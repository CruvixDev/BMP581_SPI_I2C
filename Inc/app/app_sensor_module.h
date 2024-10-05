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

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum {
  /* Define sensor types */
  TEMPERATURE,
  HUMIDITY,
  PRESSURE,
  LIGHT,
  UV_INTENSITY
} SensorType;

typedef enum {
  /* Define sensor data unit */
  DEGREE_CELSIUS,
  PERCENT,
  PASCAL,
  LUX,
  INDEX
} SensorDataUnit;

typedef struct
{
  char sensorName[50];
  SensorType sensorType;
  SensorDataUnit sensorDataUnit;
} Sensor;

typedef struct
{
  Sensor sensor; //I2CSensor extends Sensor
  uint8_t i2cAddress;
  uint8_t i2cRegisterAddress;
  uint8_t* data;
} I2CSensor;

typedef struct
{
  Sensor sensor; //SPISensor extends Sensor
  uint8_t spiFrequency;
  uint8_t spiCommand;
} SPISensor;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void vAPP_BMP581_init(void);
float fAPP_BMP581_getPressure(void);
float fAPP_BMP581_getTemperature(void);
uint8_t u8APP_BMP581_getAddress(void);
uint8_t u8APP_BMP581_getChipID(void);
uint8_t u8APP_BMP581_getChipRevision(void);
void vAPP_BMP581_startMeasurements(void);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* _SENSOR_MODULE_H */
