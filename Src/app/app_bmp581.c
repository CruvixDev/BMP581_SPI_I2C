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
  float f_pressure;
  float f_temperature;
  bool b_isBMP581Ready;
} sBMP581Sensor_t;

/* Private define ------------------------------------------------------------*/
#define BMP581_REGISTER_SIZE (uint8_t)1

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static sBMP581Sensor_t g_BMP581Sensor = {
  0x00,
  0x00,
  0x00,
  0.0f,
  0.0f,
  false
};

static sI2CSensor_t g_I2CSensor_BMP581 = {
  {"BMP581", ceApp_Sensor_PRESSURE, ceApp_Sensor_PASCAL}, //Sensor object attributes
  0x46, //BMP581 I2C address
  0x00, //BMP581 I2C register address
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

}

/**
 * @brief Get the pressure data
 * 
 * This function returns the pressure data of BMP581
 * 
 * @return float The pressure data
 */
float fAPP_BMP581_getPressure(void) {
  return 0.0f;
}

/**
 * @brief Get the temperature data
 * 
 * This function returns the temperature data of BMP581
 * 
 * @return float The temperature data
 */
float fAPP_BMP581_getTemperature(void) {
  return 0.0f;
}

/**
 * @brief Get the BMP581 I2C address
 * 
 * This function get the BMP581 I2C address
 * 
 * @return int The BMP581 I2C address
 */
uint8_t u8APP_BMP581_getAddress(void) {
  return 0u;
}

/**
 * @brief Get the BMP581 chip's ID
 * 
 * This function get the BMP581 chip's ID
 * 
 * @return int The BMP581 chip's ID
 */
uint8_t u8APP_BMP581_getChipID(void) {
  g_I2CSensor_BMP581.u8_i2cRegisterAddress = 0x01;

  vI2C_read(&g_I2CSensor_BMP581, 0x01, &g_BMP581Sensor.u8_chipID, 1);

  return 0u;
}

/**
 * @brief Get the BMP581 chip's revision
 * 
 * This function get the BMP581 chip's revision
 * 
 * @return int The BMP581 chip's revision
 */
uint8_t u8APP_BMP581_getChipRevision(void) {
  return 0u;
}

/**
 * @brief Start the measurement process
 * 
 * Start pressure and temperature measurement process of the BMP581
 * 
 * @return
 */
void vAPP_BMP581_startMeasurements(void) {

}

/* Private functions ---------------------------------------------------------*/
