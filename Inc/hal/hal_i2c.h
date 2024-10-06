/**
  ******************************************************************************
  * @file           : i2c.h
  * @brief          : This file contains all the function prototypes for
  * the i2c.c file
  * @author         : Julien Cruvieux
  * @date           : 2024/09/22
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "app/app_sensor_module.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void vI2C_init(void);
void vI2C_deInit(void);
void vI2C_transmit(sI2CSensor_t* p_pi2cSensorInfo, uint8_t* p_pu8Data, uint16_t p_u16Size);
void vI2C_receive(sI2CSensor_t* p_pi2cSensorInfo, uint8_t* p_pu8Data, uint16_t p_u16Size);
void vI2C_write(sI2CSensor_t* p_pi2cSensorInfo, uint8_t p_u8WriteAddress, uint8_t* p_pu8Data, uint16_t p_u16Size);
void vI2C_read(sI2CSensor_t* p_pi2cSensorInfo, uint8_t p_u8ReadAddress, uint8_t* p_pu8Data, uint16_t p_u16Size);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */
