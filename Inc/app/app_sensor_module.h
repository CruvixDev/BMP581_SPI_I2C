/**
  ******************************************************************************
  * @file           : sensor_module.h
  * @brief          : This file describe the Sensor object header
  * @author         : Julien Cruvieux
  * @date           : 22/09/2024
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SENSOR_MODULE_H
#define _SENSOR_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum {
  /* Define sensor types */
  ceApp_Sensor_TEMPERATURE,
  ceApp_Sensor_HUMIDITY,
  ceApp_Sensor_PRESSURE,
  ceApp_Sensor_LIGHT,
  ceApp_Sensor_UV_INTENSITY
} eSensorType_t;

typedef enum {
  /* Define sensor data unit */
  ceApp_Sensor_DEGREE_CELSIUS,
  ceApp_Sensor_PERCENT,
  ceApp_Sensor_PASCAL,
  ceApp_Sensor_LUX,
  ceApp_Sensor_INDEX
} eSensorDataUnit_t;

typedef struct
{
  char c_SensorName[50];
  eSensorType_t s_SensorType;
  eSensorDataUnit_t s_SensorDataUnit;
} sSensor_t;

typedef struct
{
  sSensor_t s_Sensor; //I2CSensor extends Sensor
  uint8_t u8_i2cAddress;
  uint8_t u8_i2cRegisterSize;
} sI2CSensor_t;

typedef struct
{
  sSensor_t s_Sensor; //SPISensor extends Sensor
  uint8_t u8_spiFrequency;
  uint8_t spiCommand;
} sSPISensor_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* _SENSOR_MODULE_H */
