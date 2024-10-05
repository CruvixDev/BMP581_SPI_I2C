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

/* Associated interfaces -----------------------------------------------------*/
#include "app/app_sensor_module.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint8_t g_u8ChipID = 0;
static uint8_t g_u8ChipRevision = 0;
static uint8_t g_u8ChipStatus = 0;
static float g_fPressure = 0.0f;
static float g_fTemperature = 0.0f;
static bool g_bIsBMP581Ready = false;

static I2CSensor g_I2CSensor_BMP581 = {
  {"BMP581", PRESSURE, PASCAL}, //Sensor object attributes
  0x00, //BMP581 I2C address
  0x00, //BMP581 I2C register address
  {0} //BMP 581 I2C data
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
