#ifndef __TIM_H
#define __TIM_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"

/* Variables ---------------------------------------------------------*/

/* Function prototypes -----------------------------------------------*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);

#endif
