/**
  ******************************************************************************
  * @file           : mx_gpio_default.c
  * @brief          : gpio_default Peripheral initialization
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
#include "mx_gpio_default.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported variables by reference -------------------------------------------*/

/******************************************************************************/
/* Exported functions for GPIO in HAL layer                                   */
/******************************************************************************/
system_status_t mx_gpio_default_init(void)
{
  hal_gpio_config_t  gpio_config;

  HAL_RCC_GPIOA_EnableClock();

  HAL_RCC_GPIOB_EnableClock();

  HAL_RCC_GPIOC_EnableClock();

  HAL_RCC_GPIOD_EnableClock();

  HAL_RCC_GPIOE_EnableClock();

  HAL_RCC_GPIOH_EnableClock();

  /*
    GPIO pin labels :
    PA14  ---------> AMP_NSD
    */
  /* Configure PA14 GPIO pin in output mode */
  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.pull            = HAL_GPIO_PULL_DOWN;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.init_state      = AMP_NSD_INIT_STATE;
  if (HAL_GPIO_Init(AMP_NSD_PORT, AMP_NSD_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PB0   ---------> CHGR_NCHG
    PB1   ---------> CHGR_NPG
    */
  /* Configure PB0, PB1 GPIO pins in input mode */
  gpio_config.mode            = HAL_GPIO_MODE_INPUT;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  if (HAL_GPIO_Init(HAL_GPIOB, CHGR_NCHG_PIN | CHGR_NPG_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PB2   ---------> DISP_NRES
    */
  /* Configure PB2 GPIO pin in output mode */
  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.init_state      = DISP_NRES_INIT_STATE;
  if (HAL_GPIO_Init(DISP_NRES_PORT, DISP_NRES_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PC0   ---------> HOME
    PC1   ---------> CW
    PC2   ---------> CCW
    PC6   ---------> SD_CD
    PC11  ---------> DAC_GPO1
    PC12  ---------> DAC_GPIO2
    PC13  ---------> SLIDE2
    PC14  ---------> SLIDE3
    PC15  ---------> VOLPLUS
    */
  /* Configure PC0, PC1, PC2, PC6, PC11, PC12, PC13, PC14, PC15 GPIO pins in input mode */
  gpio_config.mode            = HAL_GPIO_MODE_INPUT;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  if (HAL_GPIO_Init(HAL_GPIOC, HOME_PIN | CW_PIN | CCW_PIN | SD_CD_PIN | DAC_GPO1_PIN | DAC_GPIO2_PIN | SLIDE2_PIN | SLIDE3_PIN | VOLPLUS_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PC7   ---------> SD_SPI2_CS
    PC10  ---------> DAC_GPI1
    */
  /* Configure PC7, PC10 GPIO pins in output mode */
  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.init_state      = HAL_GPIO_PIN_RESET;
  if (HAL_GPIO_Init(HAL_GPIOC, SD_SPI2_CS_PIN | DAC_GPI1_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PD2   ---------> DAC_GPIO1
    */
  /* Configure PD2 GPIO pin in input mode */
  gpio_config.mode            = HAL_GPIO_MODE_INPUT;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  if (HAL_GPIO_Init(DAC_GPIO1_PORT, DAC_GPIO1_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PE2   ---------> SLIDE1
    */
  /* Configure PE2 GPIO pin in input mode */
  gpio_config.mode            = HAL_GPIO_MODE_INPUT;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  if (HAL_GPIO_Init(SLIDE1_PORT, SLIDE1_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PH0   ---------> VOLMINUS
    PH1   ---------> PLAY
    */
  /* Configure PH0, PH1 GPIO pins in input mode */
  gpio_config.mode            = HAL_GPIO_MODE_INPUT;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  if (HAL_GPIO_Init(HAL_GPIOH, VOLMINUS_PIN | PLAY_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  return SYSTEM_OK;
}

system_status_t mx_gpio_default_deinit(void)
{
  /* De-initialize pins of GPIOA port */
  HAL_GPIO_DeInit(AMP_NSD_PORT, AMP_NSD_PIN);

  /* De-initialize pins of GPIOB port */
  HAL_GPIO_DeInit(HAL_GPIOB, CHGR_NCHG_PIN | CHGR_NPG_PIN | DISP_NRES_PIN);

  /* De-initialize pins of GPIOC port */
  HAL_GPIO_DeInit(HAL_GPIOC, HOME_PIN | CW_PIN | CCW_PIN | SD_CD_PIN | SD_SPI2_CS_PIN | DAC_GPI1_PIN | DAC_GPO1_PIN | DAC_GPIO2_PIN | SLIDE2_PIN | SLIDE3_PIN | VOLPLUS_PIN);

  /* De-initialize pins of GPIOD port */
  HAL_GPIO_DeInit(DAC_GPIO1_PORT, DAC_GPIO1_PIN);

  /* De-initialize pins of GPIOE port */
  HAL_GPIO_DeInit(SLIDE1_PORT, SLIDE1_PIN);

  /* De-initialize pins of GPIOH port */
  HAL_GPIO_DeInit(HAL_GPIOH, VOLMINUS_PIN | PLAY_PIN);

  return SYSTEM_OK;
}
