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
  uint8_t u8_CMD;
  uint8_t u8_OSR_EFF;
  uint8_t u8_ODR_CONFIG;
  uint8_t u8_OSR_CONFIG;
  uint8_t u8_OOR_CONFIG;
  uint8_t u8_OOR_RANGE;
  uint8_t u8_OOR_THR_P_MSB;
  uint8_t u8_OOR_THR_P_LSB;
  uint8_t u8_DSP_IIR;
  uint8_t u8_DSP_CONFIG;
  uint8_t u8_NVM_DATA_MSB;
  uint8_t u8_NVM_DATA_LSB;
  uint8_t u8_NVM_ADDR;
  uint8_t u8_FIFO_DATA;
  uint8_t u8_STATUS;
  uint8_t u8_INT_STATUS;
  uint8_t u8_PRESS_DATA_MSB;
  uint8_t u8_PRESS_DATA_LSB;
  uint8_t u8_PRESS_DATA_XLSB;
  uint8_t u8_TEMP_DATA_MSB;
  uint8_t u8_TEMP_DATA_LSB;
  uint8_t u8_TEMP_DATA_XLSB;
  uint8_t u8_FIFO_SEL;
  uint8_t u8_FIFO_COUNT;
  uint8_t u8_FIFO_CONFIG;
  uint8_t u8_INT_SOURCE;
  uint8_t u8_INT_CONFIG;
  uint8_t u8_DRIVE_CONFIG;
  uint8_t u8_CHIP_STATUS;
  uint8_t u8_REV_ID;
  uint8_t u8_CHIP_ID;
} sBMP581Sensor_t; //Registers of BMP581 sensor object

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static sBMP581Sensor_t g_BMP581Sensor = {0};

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
  /* Read chip ID, Rev, status and state synchronously */
  vI2C_read(&g_I2CSensor_BMP581, cAPP_BMP581_REG_CHIP_ID, &g_BMP581Sensor.u8_CHIP_ID, 1);
  vI2C_read(&g_I2CSensor_BMP581, cAPP_BMP581_REG_REV_ID, &g_BMP581Sensor.u8_REV_ID, 1);
  vI2C_read(&g_I2CSensor_BMP581, cAPP_BMP581_REG_STATUS, &g_BMP581Sensor.u8_CHIP_STATUS, 1);
  vI2C_read(&g_I2CSensor_BMP581, cAPP_BMP581_REG_INT_STATUS, &g_BMP581Sensor.u8_INT_STATUS, 1);
  vI2C_read(&g_I2CSensor_BMP581, cAPP_BMP581_REG_ODR_CONFIG, &g_BMP581Sensor.u8_ODR_CONFIG, 1);

  /* Verify the retrieved data if no error */
  if 
  (
    g_BMP581Sensor.u8_CHIP_ID == BMP581_I2C_CHIP_ID && 
    g_BMP581Sensor.u8_REV_ID == BMP581_I2C_REV_ID &&
    g_BMP581Sensor.u8_INT_STATUS == BMP581_I2C_INT_STATUS_READY &&
    g_BMP581Sensor.u8_CHIP_STATUS & BMP581_I2C_STATUS_READY
  ) {
    if (g_BMP581Sensor.u8_ODR_CONFIG == ceAPP_BMP581_STANDBY) {
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
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_writeCommand(uint8_t p_u8Command) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_configureODR(sODRConfig_t p_sODRConfig) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_configureOSR(sOSRConfig_t p_sOSRConfig) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_configureOOR(sOORConfig_t p_sOORConfig) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_configureDSP(sDSPConfig_t p_sDSPConfig) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_writeNVM(uint8_t p_u8NVMAddress, uint8_t p_u8NVMData) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_readNVM(uint8_t p_u8NVMAddress, uint8_t p_u8NVMData) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_configureFIFO(sFIFOConfig_t p_sFIFOConfig) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_configureInterrupt(sIntConfig_t p_sIntConfig) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_configureDrive(sDriveConfig_t p_sDriveConfig) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getCommand(uint8_t* p_u8Command) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getODRConfig(sODRConfig_t* p_sODRConfig) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getOSRConfig(sOSRConfig_t* p_sOSRConfig) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getOORConfig(sOORConfig_t* p_sOORConfig) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getDSPConfig(sDSPConfig_t* p_sDSPConfig) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getFIFOConfig(sFIFOConfig_t* p_sFIFOConfig) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getInterruptConfig(sIntConfig_t* p_sIntConfig) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getDriveConfig(sDriveConfig_t* p_sDriveConfig) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getEffectiveOSR(sOSREff_t* p_sOSREff) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getFIFOData(uint8_t* p_u8FIFOData) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getStatus(sStatus_t* p_sStatus) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getIntStatus(sIntStatus_t* p_sIntStatus) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getPressData(sPressData_t* p_sPressData) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getTempData(sTempData_t* p_sTempData) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getFIFOCount(uint8_t* p_u8FIFOCount) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getChipStatus(sChipStatus_t* p_sChipStatus) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getChipID(uint8_t* p_u8ChipID) {

}

/**
 * @brief TODO
 * 
 * TODO
 * 
 * @return
 */
void errAPP_BMP581_getRevID(uint8_t* p_u8RevID) {

}

/* Private functions ---------------------------------------------------------*/
