#include "gpio.h"
#include "tim.h"

void L298N_Init(void)
{
	HAL_TIM_Base_Start(&htim2);									//打开定时器2
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);		//打开通道1
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);		//打开通道2
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);		//打开通道3
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);		//打开通道4
	
	HAL_TIM_Base_Start(&htim3);									//打开定时器3
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);		//打开通道1
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);		//打开通道2
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);		//打开通道3
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);		//打开通道4
}

void L298N_Front(int16_t Speed)
{
	//左前轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, Speed);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
	//左后轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, Speed);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 0);
	//右后轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, Speed);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 0);
	//右前轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, Speed);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, 0);
}

void L298N_Rear(int16_t Speed)
{
	//左前轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, Speed);
	//左后轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, Speed);
	//右后轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, Speed);
	//右前轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, Speed);
}
	
void L298N_Left(int16_t Speed)
{
	//左前轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, Speed);
	//左后轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, Speed);
	//右后轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, Speed);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 0);
	//右前轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, Speed);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, 0);
}
	
void L298N_Right(int16_t Speed)
{
	//左前轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, Speed);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
	//左后轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, Speed);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 0);
	//右后轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, Speed);
	//右前轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, Speed);
}
	
	
	
	
	
	
	
	