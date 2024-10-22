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
#ifndef _HAL_GPIO_
#define _HAL_GPIO_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Public includes -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void vHAL_GPIO_init(void);
void vHAL_GPIO_toggleGreenLED(void);
void vHAL_GPIO_toggleRedLED(void);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* _HAL_GPIO_ */
