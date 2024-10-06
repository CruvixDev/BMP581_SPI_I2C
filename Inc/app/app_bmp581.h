/**
  ******************************************************************************
  * @file           : hal_clock.h
  * @brief          : Header file for STM32 clock configuration and 
  * initialisation
  * @author         : Julien Cruvieux
  * @date           : 2024/09/30
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _APP_BMP581_
#define _APP_BMP581_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

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

#endif /* _APP_BMP581_ */
