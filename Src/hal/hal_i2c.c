/**
  ******************************************************************************
  * @file           : i2c.c
  * @brief          : This file provides code for the configuration
  * of the I2C instances.
  * @author         : Julien Cruvieux
  * @date           : 2024/09/22
  ******************************************************************************
  */

/* General interfaces --------------------------------------------------------*/

/* Used interfaces (dependencies includes ) ----------------------------------*/

/* Associated interfaces -----------------------------------------------------*/
#include "hal/hal_i2c.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static I2C_HandleTypeDef hi2c1;
static DMA_HandleTypeDef hdma_i2c1_tx;
static DMA_HandleTypeDef hdma_i2c1_rx;

/* Private function prototypes -----------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void vI2C_init(void)
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00707CBB;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  
  HAL_I2C_Init(&hi2c1);
  HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE);
  HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0);

}

/* Private functions ---------------------------------------------------------*/
void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(i2cHandle->Instance==I2C1)
  {

    /** Initializes the peripherals clock
    */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
    PeriphClkInitStruct.I2c123ClockSelection = RCC_I2C1235CLKSOURCE_D2PCLK1;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();

    /* I2C1 DMA Init */
    /* I2C1_TX Init */
    hdma_i2c1_tx.Instance = DMA1_Stream0;
    hdma_i2c1_tx.Init.Request = DMA_REQUEST_I2C1_TX;
    hdma_i2c1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_i2c1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_i2c1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_i2c1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_i2c1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_i2c1_tx.Init.Mode = DMA_NORMAL;
    hdma_i2c1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_i2c1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_Init(&hdma_i2c1_tx);

    __HAL_LINKDMA(i2cHandle,hdmatx,hdma_i2c1_tx);

    /* I2C1_RX Init */
    hdma_i2c1_rx.Instance = DMA1_Stream1;
    hdma_i2c1_rx.Init.Request = DMA_REQUEST_I2C1_RX;
    hdma_i2c1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_i2c1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_i2c1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_i2c1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_i2c1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_i2c1_rx.Init.Mode = DMA_NORMAL;
    hdma_i2c1_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_i2c1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_Init(&hdma_i2c1_rx);

    __HAL_LINKDMA(i2cHandle,hdmarx,hdma_i2c1_rx);

    /* I2C1 interrupt Init */
    HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
    HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);

  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{
  if(i2cHandle->Instance==I2C1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

    /* I2C1 DMA DeInit */
    HAL_DMA_DeInit(i2cHandle->hdmatx);
    HAL_DMA_DeInit(i2cHandle->hdmarx);

    /* I2C1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
    HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);

  }
}

void vI2C_deInit(void) {

}

void vI2C_transmit(sI2CSensor_t* p_pi2cSensorInfo, uint8_t* p_pu8Data) {
  if (p_pi2cSensorInfo != NULL) {
    HAL_I2C_Master_Transmit_DMA(
      &hi2c1, 
      (uint16_t)p_pi2cSensorInfo->u8_i2cAddress,
      p_pu8Data,
      (uint16_t)sizeof(p_pu8Data)
    );
  }
}

void vI2C_receive(sI2CSensor_t* p_pi2cSensorInfo, uint8_t* p_pu8Data) {
  if (p_pi2cSensorInfo != NULL) {
    HAL_I2C_Master_Receive_DMA(
      &hi2c1,
      (uint16_t)p_pi2cSensorInfo->u8_i2cAddress,
      p_pu8Data,
      (uint16_t)sizeof(p_pu8Data)
    );
  }
}

void vI2C_write(sI2CSensor_t* p_pi2cSensorInfo, uint8_t p_u8WriteAddress, uint8_t* p_pu8Data) {
  if (p_pi2cSensorInfo != NULL) {
    HAL_I2C_Mem_Write_DMA(
      &hi2c1,
      (uint16_t)p_pi2cSensorInfo->u8_i2cAddress,
      (uint16_t)p_u8WriteAddress,
      (uint16_t)p_pi2cSensorInfo->u8_i2cRegisterSize,
      p_pu8Data,
      (uint16_t)sizeof(p_pu8Data)
    );
  }
}

void vI2C_read(sI2CSensor_t* p_pi2cSensorInfo, uint8_t p_u8ReadAddress, uint8_t* p_pu8Data) {
  if (p_pi2cSensorInfo != NULL) {
    HAL_I2C_Mem_Read_DMA(
      &hi2c1,
      (uint16_t)p_pi2cSensorInfo->u8_i2cAddress,
      (uint16_t)p_u8ReadAddress,
      (uint16_t)p_pi2cSensorInfo->u8_i2cRegisterSize,
      p_pu8Data,
      (uint16_t)sizeof(p_pu8Data)
    );
  }
}

void DMA1_Stream0_IRQHandler(void) {
  HAL_DMA_IRQHandler(&hdma_i2c1_tx);
}

void DMA1_Stream1_IRQHandler(void) {
  HAL_DMA_IRQHandler(&hdma_i2c1_rx);
}
