/**
  ******************************************************************************
  * @file         SG90.h
  * @brief        舵机模块
	*							 This file provides firmware functions to manage the following
	*							 + 控制舵机
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* 该文件包含TIM\PWM，需要在STM32CubeMX中配置开启
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"

/* Init ----------------------------------------------------------------------*/
void SG90_Init(void)
{
	HAL_TIM_PWM_Start(&htimX, TIM_CHANNEL_X);
}

/* Define --------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/


/**
  * @brief  舵机控制
  * @param  Angle 舵机旋转的角度
  * @retval 无
  */
void SteeringEngine_Control(uint8_t Angle)
{
	uint32_t temp;
	temp = ((Angle * 12) / 180) + 3;
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, temp);
}
