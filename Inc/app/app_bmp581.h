/**
  ******************************************************************************
  * @file           : app_bmp581.h
  * @brief          : Header file for BMP581 app layer
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
#define BMP5_I2C_ADDR_PRIM (uint8_t)0x46
#define BMP5_I2C_ADDR_SEC  (uint8_t)0x47

#define cAPP_BMP581_REG_CHIP_ID         (uint8_t)0x01
#define cAPP_BMP581_REG_REV_ID          (uint8_t)0x02
#define cAPP_BMP581_REG_CHIP_STATUS     (uint8_t)0x11
#define cAPP_BMP581_REG_DRIVE_CONFIG    (uint8_t)0x13
#define cAPP_BMP581_REG_INT_CONFIG      (uint8_t)0x14
#define cAPP_BMP581_REG_INT_SOURCE      (uint8_t)0x15
#define cAPP_BMP581_REG_FIFO_CONFIG     (uint8_t)0x16
#define cAPP_BMP581_REG_FIFO_COUNT      (uint8_t)0x17
#define cAPP_BMP581_REG_FIFO_SEL        (uint8_t)0x18
#define cAPP_BMP581_REG_TEMP_DATA_XLSB  (uint8_t)0x1D
#define cAPP_BMP581_REG_TEMP_DATA_LSB   (uint8_t)0x1E
#define cAPP_BMP581_REG_TEMP_DATA_MSB   (uint8_t)0x1F
#define cAPP_BMP581_REG_PRESS_DATA_XLSB (uint8_t)0x20
#define cAPP_BMP581_REG_PRESS_DATA_LSB  (uint8_t)0x21
#define cAPP_BMP581_REG_PRESS_DATA_MSB  (uint8_t)0x22
#define cAPP_BMP581_REG_INT_STATUS      (uint8_t)0x27
#define cAPP_BMP581_REG_STATUS          (uint8_t)0x28
#define cAPP_BMP581_REG_FIFO_DATA       (uint8_t)0x29
#define cAPP_BMP581_REG_NVM_ADDR        (uint8_t)0x2B
#define cAPP_BMP581_REG_NVM_DATA_LSB    (uint8_t)0x2C
#define cAPP_BMP581_REG_NVM_DATA_MSB    (uint8_t)0x2D
#define cAPP_BMP581_REG_DSP_CONFIG      (uint8_t)0x30
#define cAPP_BMP581_REG_DSP_IIR         (uint8_t)0x31
#define cAPP_BMP581_REG_OOR_THR_P_LSB   (uint8_t)0x32
#define cAPP_BMP581_REG_OOR_THR_P_MSB   (uint8_t)0x33
#define cAPP_BMP581_REG_OOR_RANGE       (uint8_t)0x34
#define cAPP_BMP581_REG_OOR_CONFIG      (uint8_t)0x35
#define cAPP_BMP581_REG_OSR_CONFIG      (uint8_t)0x36
#define cAPP_BMP581_REG_ODR_CONFIG      (uint8_t)0x37
#define cAPP_BMP581_REG_OSR_EFF         (uint8_t)0x38
#define cAPP_BMP581_REG_CMD             (uint8_t)0x7E

#define BMP581_REGISTER_SIZE (uint8_t)1

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
