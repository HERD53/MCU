#include "gpio.h"
#include "tim.h"

void L258N_Ctrl(int16_t val)
{
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	
	if (val > 0)
	{
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, val);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
	}
	else
	{
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 0);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, -val);
	}
}
