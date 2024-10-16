/**
  ******************************************************************************
  * @file           : i2c.c
  * @brief          : This file provides code for I2C configuration
  * of the I2C instances.
  * @author         : Julien Cruvieux
  * @date           : 2024/09/22
  ******************************************************************************
  */

/* General interfaces --------------------------------------------------------*/

/* Used interfaces (dependencies includes ) ----------------------------------*/
#include "stm32h7xx_hal.h"

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

/**
 * @brief Init function for I2C peripheral
 * 
 * Initialise I2C Peripheral and filters
 * 
 * @return
 */
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

/**
 * @brief Init function for DMA and GPIO 
 * 
 * Initialises the DMA channels and GPIO of I2C peripheral
 * 
 * @param i2cHandle the structure containing all configurations of I2C peripheral
 * @return
 */
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
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
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

/**
 * @brief Deinit function for DMA and GPIO 
 * 
 * De-initialises the DMA channels and GPIO of I2C peripheral
 * 
 * @param i2cHandle the structure containing all configurations of I2C peripheral
 * @return
 */
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

/**
 * @brief Deinit function for I2C 
 * 
 * De-initialises the I2C peripheral
 * 
 * @return
 */
void vI2C_deInit(void) {

}

/**
 * @brief Transmit function on I2C bus
 * 
 * Transmit data over I2C bus in DMA mode
 * 
 * @param p_pi2cSensorInfo the I2C sensor object to transmit
 * @param p_pu8Data the data array to transmit
 * @param p_u16Size the size of the data array to transmit
 * @return
 */
void vI2C_transmit(sI2CSensor_t* p_pi2cSensorInfo, uint8_t* p_pu8Data, uint16_t p_u16Size) {
  if (p_pi2cSensorInfo != NULL) {
    HAL_I2C_Master_Transmit_DMA(
      &hi2c1, 
      (uint16_t)p_pi2cSensorInfo->u8_i2cAddress,
      p_pu8Data,
      p_u16Size //In bytes
    );
  }
}

/**
 * @brief Receive function on I2C bus
 * 
 * Receive data over I2C bus in DMA mode
 * 
 * @param p_pi2cSensorInfo the I2C sensor object to receive
 * @param p_pu8Data the data array to receive
 * @param p_u16Size the size of the data array to receive
 * @return
 */
void vI2C_receive(sI2CSensor_t* p_pi2cSensorInfo, uint8_t* p_pu8Data, uint16_t p_u16Size) {
  if (p_pi2cSensorInfo != NULL) {
    HAL_I2C_Master_Receive_DMA(
      &hi2c1,
      (uint16_t)p_pi2cSensorInfo->u8_i2cAddress,
      p_pu8Data,
      p_u16Size //In bytes
    );
  }
}

/**
 * @brief Write data to I2C device
 * 
 * Write data into I2C device internal's register
 * 
 * @param p_pi2cSensorInfo the I2C sensor object to write
 * @param p_u8WriteAddress the I2C register address to write data
 * @param p_pu8Data the data array to write into I2C device's register
 * @param p_u16Size the size of the data array to write
 * @return
 */
void vI2C_write(sI2CSensor_t* p_pi2cSensorInfo, uint8_t p_u8WriteAddress, uint8_t* p_pu8Data, uint16_t p_u16Size) {
  if (p_pi2cSensorInfo != NULL) {
    HAL_I2C_Mem_Write_DMA(
      &hi2c1,
      (uint16_t)p_pi2cSensorInfo->u8_i2cAddress,
      (uint16_t)p_u8WriteAddress,
      (uint16_t)p_pi2cSensorInfo->u8_i2cRegisterSize,
      p_pu8Data,
      p_u16Size //In bytes
    );
  }
}

/**
 * @brief Read data from I2C device
 * 
 * Read data into I2C device internal's register
 * 
 * @param p_pi2cSensorInfo the I2C sensor object to read
 * @param p_u8WriteAddress the I2C register address to read data
 * @param p_pu8Data the data array to read into I2C device's register
 * @param p_u16Size the size of the data array to read
 * @return
 */
void vI2C_read(sI2CSensor_t* p_pi2cSensorInfo, uint8_t p_u8ReadAddress, uint8_t* p_pu8Data, uint16_t p_u16Size) {
  if (p_pi2cSensorInfo != NULL) {
    HAL_I2C_Mem_Read_DMA(
      &hi2c1,
      (uint16_t)p_pi2cSensorInfo->u8_i2cAddress << 1, //Left shift of one byte for the HAL needed
      (uint16_t)p_u8ReadAddress,
      (uint16_t)p_pi2cSensorInfo->u8_i2cRegisterSize,
      p_pu8Data,
      p_u16Size //In bytes
    );
  }
}

void I2C1_EV_IRQHandler(void) {
  HAL_I2C_EV_IRQHandler(&hi2c1);
}

void I2C1_ER_IRQHandler(void) {
  HAL_I2C_ER_IRQHandler(&hi2c1);
}

void DMA1_Stream0_IRQHandler(void) {
  HAL_DMA_IRQHandler(&hdma_i2c1_tx);
}

void DMA1_Stream1_IRQHandler(void) {
  HAL_DMA_IRQHandler(&hdma_i2c1_rx);
}

/* Private functions ---------------------------------------------------------*/
