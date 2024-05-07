#include "gpio.h"
#include "tim.h"
#include "Delay.h"

#define GPIOX GPIOA
#define Tx GPIO_PIN_1

uint32_t distance;
uint32_t first;
uint32_t later;
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim2 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
	{
		first = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
		later = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2);
		distance = ((later - first) * 34) / 2000;
		if (first > later) distance = -1;
	}
}
/**
  * @brief  超声波测距是用定时器2的输入捕获功能，测出高电平的时间。从而得出与最近障碍物的距离
  * @param  无
  * @retval 和最近障碍物距离	单位：(cm)
  */
void Ultr_Send(void)
{
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
	
	HAL_GPIO_WritePin(GPIOX, Tx, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOX, Tx, GPIO_PIN_RESET);
	
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	
	HAL_Delay(50);
}

