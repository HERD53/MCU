/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "HC_06.h"
#include "Infrared_Tracking.h"
#include "OLED.h"
#include "OLED_Data.h"
#include "Rotary_Encoder.h"
#include "TIM_CallBack.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PWMA_1_Pin GPIO_PIN_0
#define PWMA_1_GPIO_Port GPIOA
#define PWMB_1_Pin GPIO_PIN_1
#define PWMB_1_GPIO_Port GPIOA
#define PWMA_2_Pin GPIO_PIN_2
#define PWMA_2_GPIO_Port GPIOA
#define PWMB_2_Pin GPIO_PIN_3
#define PWMB_2_GPIO_Port GPIOA
#define Buzzer_Pin GPIO_PIN_5
#define Buzzer_GPIO_Port GPIOA
#define Encoder_1_Pin GPIO_PIN_6
#define Encoder_1_GPIO_Port GPIOA
#define Encoder_2_Pin GPIO_PIN_7
#define Encoder_2_GPIO_Port GPIOA
#define Encoder_3_Pin GPIO_PIN_0
#define Encoder_3_GPIO_Port GPIOB
#define Encoder_4_Pin GPIO_PIN_1
#define Encoder_4_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_11
#define OLED_SDA_GPIO_Port GPIOB
#define BIN2_2_Pin GPIO_PIN_12
#define BIN2_2_GPIO_Port GPIOB
#define BIN1_2_Pin GPIO_PIN_13
#define BIN1_2_GPIO_Port GPIOB
#define AIN1_2_Pin GPIO_PIN_14
#define AIN1_2_GPIO_Port GPIOB
#define AIN2_2_Pin GPIO_PIN_15
#define AIN2_2_GPIO_Port GPIOB
#define BIN2_1_Pin GPIO_PIN_8
#define BIN2_1_GPIO_Port GPIOA
#define BIN1_1_Pin GPIO_PIN_11
#define BIN1_1_GPIO_Port GPIOA
#define AIN2_1_Pin GPIO_PIN_12
#define AIN2_1_GPIO_Port GPIOA
#define AIN1_1_Pin GPIO_PIN_15
#define AIN1_1_GPIO_Port GPIOA
#define Infrared_5_Pin GPIO_PIN_3
#define Infrared_5_GPIO_Port GPIOB
#define Infrared_4_Pin GPIO_PIN_4
#define Infrared_4_GPIO_Port GPIOB
#define Infrared_3_Pin GPIO_PIN_5
#define Infrared_3_GPIO_Port GPIOB
#define Infrared_2_Pin GPIO_PIN_6
#define Infrared_2_GPIO_Port GPIOB
#define Infrared_1_Pin GPIO_PIN_7
#define Infrared_1_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_8
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_9
#define SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
