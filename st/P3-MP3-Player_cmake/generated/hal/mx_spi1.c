/**
  ******************************************************************************
  * @file           : mx_spi1.c
  * @brief          : SPI1 Peripheral initialization
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the mx_stm32c5xx_hal_drivers_license.md file
  * in the same directory as the generated code.
  * If no mx_stm32c5xx_hal_drivers_license.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "mx_spi1.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_i2s_handle_t hSPI1;
/******************************************************************************/
/* Exported functions for I2S in HAL layer */
/******************************************************************************/
hal_i2s_handle_t *mx_spi1_i2s_init(void)
{
  hal_i2s_master_config_t i2s_config;

  if (HAL_I2S_Init(&hSPI1, HAL_I2S1) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_SPI1_EnableClock();

  if (HAL_RCC_SPI1_SetKernelClkSource(HAL_RCC_SPI1_CLK_SRC_AUDIOCLK) != HAL_OK)
  {
    return NULL;
  }

  i2s_config.mode = HAL_I2S_MODE_MASTER_FULL_DUPLEX;
  i2s_config.standard = HAL_I2S_STANDARD_PHILIPS;
  i2s_config.data_format = HAL_I2S_DATA_FORMAT_16_BIT;
  i2s_config.audio_frequency = HAL_I2S_MASTER_AUDIO_FREQ_44_KHZ;
  i2s_config.clock_polarity = HAL_I2S_CLOCK_POLARITY_LOW;
  i2s_config.bit_order = HAL_I2S_MSB_FIRST;

  if (HAL_I2S_MASTER_SetConfig(&hSPI1, &i2s_config) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_I2S_SetFifoThreshold(&hSPI1, HAL_I2S_FIFO_THRESHOLD_1_DATA) != HAL_OK)
  {
    return NULL;
  }

  /* ### SPI1 GPIO Configuration ########################### */
  /* GPIO Clocks activation */
  HAL_RCC_GPIOB_EnableClock();

  HAL_RCC_GPIOA_EnableClock();

  hal_gpio_config_t  gpio_config;

  /**
    [GPIO Pin] ------> [Signal Name] ------> [Labels]

       PB3     ------>   I2S1_CK   ------>  DAC_I2S1_BLCK
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_config.alternate   = HAL_GPIO_AF_5;
  HAL_GPIO_Init(DAC_I2S1_BLCK_PORT, DAC_I2S1_BLCK_PIN, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name] ------> [Labels]

       PA15    ------>   I2S1_WS   ------>  DAC_I2S1_FSYNC
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_UP;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_5;
  HAL_GPIO_Init(DAC_I2S1_FSYNC_PORT, DAC_I2S1_FSYNC_PIN, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name] ------> [Labels]

       PB5     ------>   I2S1_SDO   ------>  DAC_I2S1_SDO
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_5;
  HAL_GPIO_Init(DAC_I2S1_SDO_PORT, DAC_I2S1_SDO_PIN, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name] ------> [Labels]

       PB4     ------>   I2S1_SDI   ------>  DAC_I2S1_SDI
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_UP;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_5;
  HAL_GPIO_Init(DAC_I2S1_SDI_PORT, DAC_I2S1_SDI_PIN, &gpio_config);

  return &hSPI1;
}

void mx_spi1_i2s_deinit(void)
{
  (void)HAL_I2S_DeInit(&hSPI1);

  HAL_RCC_SPI1_Reset();

  HAL_RCC_SPI1_DisableClock();

  /* De-initialize all GPIOB pins associated with SPI1 */
  HAL_GPIO_DeInit(HAL_GPIOB, DAC_I2S1_BLCK_PIN | DAC_I2S1_SDI_PIN | DAC_I2S1_SDO_PIN);

  /* De-initialize all GPIOA pins associated with SPI1 */
  HAL_GPIO_DeInit(DAC_I2S1_FSYNC_PORT, DAC_I2S1_FSYNC_PIN);
 }

hal_i2s_handle_t *mx_spi1_i2s_gethandle(void)
{
  return &hSPI1;
}
