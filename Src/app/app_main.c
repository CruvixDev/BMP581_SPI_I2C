/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : main program
  * @author         : Julien Cruvieux
  * @date           : 2024/09/22
  ******************************************************************************
  */

/* General interfaces --------------------------------------------------------*/

/* Associated interfaces -----------------------------------------------------*/
#include "app/app_main.h"

/* Used interfaces (dependencies includes) -----------------------------------*/
#include "hal/hal_dma.h"
#include "hal/hal_i2c.h"
#include "hal/hal_spi.h"
#include "hal/hal_gpio.h"
#include "hal/hal_clock.h"
#include "hal/hal_mpu.h"
#include "app/app_bmp581.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * 
  * @return int
  */
int main(void)
{
  /* MPU Configuration--------------------------------------------------------*/
  vHAL_MPU_init();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  vHAL_Clock_init();

  /* Initialize all configured peripherals */
  vHAL_GPIO_init();
  vHAL_DMA_init();
  vI2C_init();
  vSPI_init();

  u8APP_BMP581_getChipID();

  /* Main infinite loop */
  while (1) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
    HAL_Delay(1000);
  }
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function is executed in case of error occurrence.
  * 
  * @return None
  */
void Error_Handler(void)
{
  __disable_irq();

  while (1) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
    HAL_Delay(1000);
  }
}
