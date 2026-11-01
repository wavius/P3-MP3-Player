/**
  ******************************************************************************
  * @file           : mx_gpio_default.h
  * @brief          : Header for mx_gpio_default.c file.
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
#ifndef MX_GPIO_DEFAULT_H
#define MX_GPIO_DEFAULT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"
#include "mx_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/******************************************************************************/
/* Exported defines for gpio_default in HAL layer                             */
/******************************************************************************/

/* Primary aliases for GPIO PA14(JTCK/SWCLK) pin */
#define AMP_NSD_PORT                                    HAL_GPIOA
#define AMP_NSD_PIN                                     HAL_GPIO_PIN_14
#define AMP_NSD_INIT_STATE                              HAL_GPIO_PIN_RESET
#define AMP_NSD_ACTIVE_STATE                            HAL_GPIO_PIN_SET
#define AMP_NSD_INACTIVE_STATE                          HAL_GPIO_PIN_RESET

/* Primary aliases for GPIO PB0 pin */
#define CHGR_NCHG_PORT                                  HAL_GPIOB
#define CHGR_NCHG_PIN                                   HAL_GPIO_PIN_0

/* Primary aliases for GPIO PB1 pin */
#define CHGR_NPG_PORT                                   HAL_GPIOB
#define CHGR_NPG_PIN                                    HAL_GPIO_PIN_1

/* Primary aliases for GPIO PB2 pin */
#define DISP_NRES_PORT                                  HAL_GPIOB
#define DISP_NRES_PIN                                   HAL_GPIO_PIN_2
#define DISP_NRES_INIT_STATE                            HAL_GPIO_PIN_RESET
#define DISP_NRES_ACTIVE_STATE                          HAL_GPIO_PIN_SET
#define DISP_NRES_INACTIVE_STATE                        HAL_GPIO_PIN_RESET

/* Primary aliases for GPIO PC0 pin */
#define HOME_PORT                                       HAL_GPIOC
#define HOME_PIN                                        HAL_GPIO_PIN_0

/* Primary aliases for GPIO PC1 pin */
#define CW_PORT                                         HAL_GPIOC
#define CW_PIN                                          HAL_GPIO_PIN_1

/* Primary aliases for GPIO PC2 pin */
#define CCW_PORT                                        HAL_GPIOC
#define CCW_PIN                                         HAL_GPIO_PIN_2

/* Primary aliases for GPIO PC6 pin */
#define SD_CD_PORT                                      HAL_GPIOC
#define SD_CD_PIN                                       HAL_GPIO_PIN_6

/* Primary aliases for GPIO PC7 pin */
#define SD_SPI2_CS_PORT                                 HAL_GPIOC
#define SD_SPI2_CS_PIN                                  HAL_GPIO_PIN_7
#define SD_SPI2_CS_INIT_STATE                           HAL_GPIO_PIN_RESET
#define SD_SPI2_CS_ACTIVE_STATE                         HAL_GPIO_PIN_SET
#define SD_SPI2_CS_INACTIVE_STATE                       HAL_GPIO_PIN_RESET

/* Primary aliases for GPIO PC10 pin */
#define DAC_GPI1_PORT                                   HAL_GPIOC
#define DAC_GPI1_PIN                                    HAL_GPIO_PIN_10
#define DAC_GPI1_INIT_STATE                             HAL_GPIO_PIN_RESET
#define DAC_GPI1_ACTIVE_STATE                           HAL_GPIO_PIN_SET
#define DAC_GPI1_INACTIVE_STATE                         HAL_GPIO_PIN_RESET

/* Primary aliases for GPIO PC11 pin */
#define DAC_GPO1_PORT                                   HAL_GPIOC
#define DAC_GPO1_PIN                                    HAL_GPIO_PIN_11

/* Primary aliases for GPIO PC12 pin */
#define DAC_GPIO2_PORT                                  HAL_GPIOC
#define DAC_GPIO2_PIN                                   HAL_GPIO_PIN_12

/* Primary aliases for GPIO PC13 pin */
#define SLIDE2_PORT                                     HAL_GPIOC
#define SLIDE2_PIN                                      HAL_GPIO_PIN_13

/* Primary aliases for GPIO PC14-OSC32_IN(OSC32_IN) pin */
#define SLIDE3_PORT                                     HAL_GPIOC
#define SLIDE3_PIN                                      HAL_GPIO_PIN_14

/* Primary aliases for GPIO PC15-OSC32_OUT(OSC32_OUT) pin */
#define VOLPLUS_PORT                                    HAL_GPIOC
#define VOLPLUS_PIN                                     HAL_GPIO_PIN_15

/* Primary aliases for GPIO PD2 pin */
#define DAC_GPIO1_PORT                                  HAL_GPIOD
#define DAC_GPIO1_PIN                                   HAL_GPIO_PIN_2

/* Primary aliases for GPIO PE2 pin */
#define SLIDE1_PORT                                     HAL_GPIOE
#define SLIDE1_PIN                                      HAL_GPIO_PIN_2

/* Primary aliases for GPIO PH0-OSC_IN(PH0) pin */
#define VOLMINUS_PORT                                   HAL_GPIOH
#define VOLMINUS_PIN                                    HAL_GPIO_PIN_0

/* Primary aliases for GPIO PH1-OSC_OUT(PH1) pin */
#define PLAY_PORT                                       HAL_GPIOH
#define PLAY_PIN                                        HAL_GPIO_PIN_1

/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for gpio_default in HAL layer                           */
/******************************************************************************/
/**
  * @brief mx_gpio_default init function
  * This function configures the hardware resources used in this example
  * @retval 0  GPIO group correctly initialized
  * @retval -1 Issue detected during GPIO group initialization
  */
system_status_t mx_gpio_default_init(void);

/**
  * @brief  De-initialize gpio_default instance.
  */
system_status_t mx_gpio_default_deinit(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_GPIO_DEFAULT_H */
