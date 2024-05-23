#ifndef __Key_H
#define __Key_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"

/* Variables -----------------------------------------------------------------*/
extern uint8_t Key_Tim_Flag;
extern uint8_t Key_Flag;
extern uint8_t angle;

/* Function prototypes -------------------------------------------------------*/
void Key_Init(void);
void Key_Detection(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif
