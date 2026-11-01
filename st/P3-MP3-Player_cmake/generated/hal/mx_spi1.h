/**
  ******************************************************************************
  * @file           : mx_spi1.h
  * @brief          : Header for mx_spi1.c file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_SPI1_H
#define MX_SPI1_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** Primary aliases for I2S1_CK pin */
#define DAC_I2S1_BLCK_PORT                    HAL_GPIOB
#define DAC_I2S1_BLCK_PIN                     HAL_GPIO_PIN_3

/** Primary aliases for I2S1_WS pin */
#define DAC_I2S1_FSYNC_PORT                   HAL_GPIOA
#define DAC_I2S1_FSYNC_PIN                    HAL_GPIO_PIN_15

/** Primary aliases for I2S1_SDO pin */
#define DAC_I2S1_SDO_PORT                     HAL_GPIOB
#define DAC_I2S1_SDO_PIN                      HAL_GPIO_PIN_5

/** Primary aliases for I2S1_SDI pin */
#define DAC_I2S1_SDI_PORT                     HAL_GPIOB
#define DAC_I2S1_SDI_PIN                      HAL_GPIO_PIN_4
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for I2S in HAL layer */
/******************************************************************************/
/**
  * @brief mx_spi1_i2s init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_i2s_handle_t *mx_spi1_i2s_init(void);

/**
  * @brief  De-initialize spi1 instance and return it.
  */
void mx_spi1_i2s_deinit(void);

/**
  * @brief  Get the SPI1 object.
  * @retval Pointer on the SPI1 Handle
  */
hal_i2s_handle_t *mx_spi1_i2s_gethandle(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_SPI1_H */
