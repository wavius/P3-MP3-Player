
/**
  ******************************************************************************
  * @file           : mx_rcc.c
  * @brief          : STM32 RCC program body
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
#include "mx_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/

/******************************************************************************/
/* Exported functions for RCC in HAL layer */
/******************************************************************************/

/**
  * Configure the system core clock only and activate it using the HAL RCC unitary APIs (footprint optimization)
  *         The system Clock is configured as follow :
  *            System Clock source            = HSIDIV3
  *            SYSCLK(Hz)                     = 48000000
  *            HCLK(Hz)                       = 48000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            APB3 Prescaler                 = 1
  *            Flash Latency(WS)              = 4
  */
system_status_t mx_rcc_init(void)
{
  if (HAL_RCC_HSIDIV3_Enable() != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  /** Initializes the CPU, AHB and APB busses clocks */
  hal_rcc_bus_clk_config_t config_bus;
  config_bus.hclk_prescaler  = HAL_RCC_HCLK_PRESCALER1;
  config_bus.pclk1_prescaler = HAL_RCC_PCLK_PRESCALER1;
  config_bus.pclk2_prescaler = HAL_RCC_PCLK_PRESCALER1;
  config_bus.pclk3_prescaler = HAL_RCC_PCLK_PRESCALER1;
  if (HAL_RCC_SetBusClockConfig(&config_bus) != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  if (HAL_RCC_SetSYSCLKSource(HAL_RCC_SYSCLK_SRC_HSIDIV3) != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  /** Frequency will be decreased */
  HAL_FLASH_ITF_SetLatency(HAL_FLASH, HAL_FLASH_ITF_LATENCY_4);
  HAL_FLASH_ITF_SetProgrammingDelay(HAL_FLASH, HAL_FLASH_ITF_PROGRAM_DELAY_2);

  if (HAL_UpdateCoreClock() != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  /* ### RCC GPIO Configuration ########################### */
  /* GPIO Clocks activation */
  HAL_RCC_GPIOC_EnableClock();

  hal_gpio_config_t  gpio_config;

  /**
    [GPIO Pin] ------> [Signal Name] ------> [Labels]

       PC9     ------>   RCC_AUDIOCLK   ------>  CLK_22_5792M
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_5;
  HAL_GPIO_Init(CLK_22_5792M_PORT, CLK_22_5792M_PIN, &gpio_config);

  return SYSTEM_OK;
}

void mx_rcc_deinit(void)
{
  HAL_RCC_Reset();
}

/**
  * configures and activate the clocks used by all the peripherals selected within the project
  */
system_status_t mx_rcc_peripherals_clock_config(void)
{
  /* Peripherals using PCLK1 (48 MHz):
    I2C1
    SPI2
  */

  /* Peripherals using AUDIOCLK (22.579 MHz):
    SPI1
  */

  /* Peripherals using HSIDIV3 (48 MHz):
    USB_DRD_FS
  */
  /* HSIDIV3 already enabled inside mx_rcc_init() */

  /* Peripherals using PSIK (100 MHz):
    I2C2
  */
  if (HAL_RCC_HSIS_Enable() != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

    hal_rcc_psi_config_t config_psi;
  config_psi.psi_source = HAL_RCC_PSI_SRC_HSI_8MHz;
  config_psi.psi_ref = HAL_RCC_PSI_REF_8MHZ;
  config_psi.psi_out = HAL_RCC_PSI_OUT_100MHZ;
  if (HAL_RCC_PSI_SetConfig(&config_psi) != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  if (HAL_RCC_PSIK_Enable(HAL_RCC_PSIK_DIV1) != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  return SYSTEM_OK;
}
