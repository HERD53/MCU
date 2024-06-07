/**
  ******************************************************************************
  * @file         Motor_Driver.c
  * @brief        电机驱动模块
	*							 This file provides firmware functions to manage the following
	*							 + 驱动电机
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* 该文件包含TIM，需要在STM32CubeMX中配置开启
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"

/* Init ----------------------------------------------------------------------*/
void Car_Init(void)
{
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_Base_Start(&htim3);
	
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 0);
	
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, 0);
}

/* Define --------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

//最低速为40
void Car_Forward(uint8_t Speed)
{
	//左前轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, Speed);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 0);
	//左后轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, Speed);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 0);
	//右前轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, Speed);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, 0);
	//右后轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, Speed);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
}

void Car_Backwards(uint8_t Speed)
{
	//左前轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, Speed);
	//左后轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, Speed);
	//右前轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, Speed);
	//右后轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, Speed);
}

void Car_Left(uint8_t Speed)
{
	//左前轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, Speed);
	//左后轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, Speed);
	//右前轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, Speed);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, 0);
	//右后轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, Speed);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
}

void Car_Right(uint8_t Speed)
{
	//左前轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, Speed);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 0);
	//左后轮
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, Speed);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 0);
	//右前轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, Speed);
	//右后轮
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, Speed);
}
