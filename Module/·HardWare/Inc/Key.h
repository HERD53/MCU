#ifndef __Key_H
#define __Key_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"

/* Private define ------------------------------------------------------------*/
#define GPIOX GPIOB							//GPIOX (X...A,B,C)
#define GPIO_PIN_X GPIO_PIN_12		//GPIO_PIN_X (X...0,1,2,3,4,5,6,7)

/* Private variables ---------------------------------------------------------*/
extern uint8_t Key_Tim_Flag;
extern uint8_t Key_Flag;

/* Private function prototypes -----------------------------------------------*/
void Key_LongPress(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif
