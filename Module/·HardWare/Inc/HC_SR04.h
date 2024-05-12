#ifndef __HC_SR04_H
#define __HC_SR04_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"

/* Private define ------------------------------------------------------------*/
#define GPIOX GPIOA
#define GPIO_PIN_X GPIO_PIN_1

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
uint32_t Ultrasonic_Ranging(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

#endif
