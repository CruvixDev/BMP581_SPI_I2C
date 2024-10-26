/**
  ******************************************************************************
  * @file           : SensorModule.c
  * @brief          : This file describes the sensor objects
  * @author         : Julien Cruvieux
  * @date           : 2024/09/22
  ******************************************************************************
  */

/* General interfaces --------------------------------------------------------*/

/* Used interfaces (dependencies includes ) ----------------------------------*/
#include "app/app_bmp581.h"

/* Associated interfaces -----------------------------------------------------*/
#include "app/app_sensor_module.h"
#include "hal/hal_i2c.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  uint8_t u8_chipID;
  uint8_t u8_chipRevision;
  uint8_t u8_chipStatus;
  uint8_t u8_intStatus;
  eBMP581State_t e_bmp581State;
  float f_pressure;
  float f_temperature;
  bool b_isBMP581Ready;
} sBMP581Sensor_t; //Attributes of BMP581 sensor object

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static sBMP581Sensor_t g_BMP581Sensor = {
  0x00,
  0x00,
  0x00,
  0x00,
  ceAPP_BMP581_STANDBY,
  0.0f,
  0.0f,
  false
};

static sI2CSensor_t g_I2CSensor_BMP581 = {
  {"BMP581", ceApp_Sensor_PRESSURE, ceApp_Sensor_PASCAL}, //Sensor object attributes
  BMP581_I2C_ADDR_PRIM, //BMP581 I2C address
  BMP581_REGISTER_SIZE
};

/* Private function prototypes -----------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
 * @brief Initialises the I2C BMP581 sensor
 * 
 * This function initialises the BMP581 I2C sensor
 * 
 * @return
 */
void vAPP_BMP581_init(void) {
  uint8_t l_u8_odr_config = 0;

  /* Read chip ID, Rev, status and state synchronously */
  vI2C_read(&g_I2CSensor_BMP581, cAPP_BMP581_REG_CHIP_ID, &g_BMP581Sensor.u8_chipID, 1);
  vI2C_read(&g_I2CSensor_BMP581, cAPP_BMP581_REG_REV_ID, &g_BMP581Sensor.u8_chipRevision, 1);
  vI2C_read(&g_I2CSensor_BMP581, cAPP_BMP581_REG_STATUS, &g_BMP581Sensor.u8_chipStatus, 1);
  vI2C_read(&g_I2CSensor_BMP581, cAPP_BMP581_REG_INT_STATUS, &g_BMP581Sensor.u8_intStatus, 1);
  vI2C_read(&g_I2CSensor_BMP581, cAPP_BMP581_REG_ODR_CONFIG, &l_u8_odr_config, 1);

  g_BMP581Sensor.e_bmp581State = l_u8_odr_config & 0x03; //Read the pwr_mode bits in ODR_CONFIG register

  /* Verify the retrieved data if no error */
  if 
  (
    g_BMP581Sensor.u8_chipID == BMP581_I2C_CHIP_ID && 
    g_BMP581Sensor.u8_chipRevision == BMP581_I2C_REV_ID &&
    g_BMP581Sensor.u8_intStatus == BMP581_I2C_INT_STATUS_READY &&
    g_BMP581Sensor.u8_chipStatus & BMP581_I2C_STATUS_READY
  ) {
    if (g_BMP581Sensor.e_bmp581State == ceAPP_BMP581_STANDBY) {
      /* Enable pressure measurements */
      vI2C_write_DMA(&g_I2CSensor_BMP581, cAPP_BMP581_REG_OSR_CONFIG, 0x40, 1);
      /* Configure ODR to 240Hz */
      vI2C_write_DMA(&g_I2CSensor_BMP581, cAPP_BMP581_REG_ODR_CONFIG, 0x00, 1);
      /* Configure OSR (TBD) */
      //TODO
      /* Enable FIFO for Pressure and Temperature */
      vI2C_write_DMA(&g_I2CSensor_BMP581, cAPP_BMP581_REG_FIFO_SEL, 0x03, 1);
      /* Confifure FIFO to be stop on full */
      vI2C_write_DMA(&g_I2CSensor_BMP581, cAPP_BMP581_REG_FIFO_CONFIG, 0x20, 1);
      /* Enable IIR filter (TBD) */
      //TODO
      /* Configure interrupts (INT_CONFIG) */
      vI2C_write_DMA(&g_I2CSensor_BMP581, cAPP_BMP581_REG_INT_CONFIG, 0x0E, 1);
      /* Activate FIFO full interrupt (INT_SOURCE register) */
      vI2C_write_DMA(&g_I2CSensor_BMP581, cAPP_BMP581_REG_INT_SOURCE, 0x02, 1);

    }
    else {
      //TODO return error code : can't init
    }
  }
  else {
    //TODO return error code : can't init
  }
}

/**
 * @brief Get the BMP581 chip's ID
 * 
 * This function get the BMP581 chip's ID
 * 
 * @return int The BMP581 chip's ID
 */
uint8_t u8APP_BMP581_getChipID(void) {
  return g_BMP581Sensor.u8_chipID;
}

/**
 * @brief Get the BMP581 chip's revision
 * 
 * This function get the BMP581 chip's revision
 * 
 * @return int The BMP581 chip's revision
 */
uint8_t u8APP_BMP581_getChipRevision(void) {
  return g_BMP581Sensor.u8_chipRevision;
}

/**
 * @brief Get the BMP581 chip's state
 * 
 * This function get the BMP581 chip's state
 * 
 * @return enum The BMP581 chip's state
 */
eBMP581State_t eAPP_BMP581_getChipState(void) {
  return g_BMP581Sensor.e_bmp581State;
}

/**
 * @brief Get the pressure data
 * 
 * This function returns the pressure data of BMP581
 * 
 * @return float The pressure data
 */
float fAPP_BMP581_getPressure(void) {
  return g_BMP581Sensor.f_pressure;
}

/**
 * @brief Get the temperature data
 * 
 * This function returns the temperature data of BMP581
 * 
 * @return float The temperature data
 */
float fAPP_BMP581_getTemperature(void) {
  return g_BMP581Sensor.f_temperature;
}

/**
 * @brief Start the measurement process
 * 
 * Start pressure and temperature measurement process of the BMP581
 * 
 * @return
 */
void vAPP_BMP581_startMeasurements(void) {
  //Enable the normal mode
}

/* Private functions ---------------------------------------------------------*/
