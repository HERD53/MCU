#ifndef __HC_SR04_H
#define __HC_SR04_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"

/* Variables -----------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
uint32_t Ultrasonic_Ranging(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

#endif
