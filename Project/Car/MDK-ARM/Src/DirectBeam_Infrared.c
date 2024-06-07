/**
  ******************************************************************************
  * @file         DirectBeam_Infrared.c
  * @brief        对射式红外模块
	*							 This file provides firmware functions to manage the following
	*							 + 检测对射式红外模块被遮挡的次数
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* 该文件包含TIM\输入捕获，需要在STM32CubeMX中配置开启
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"

/* Init ----------------------------------------------------------------------*/
void DirectBeam_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
}

/* Define --------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
uint16_t DirectBeam_Count;
float Angle_Speed;
float Speed;

/**
  * @brief  TIM 输入捕获中断回调函数
  * @param  htim TIM的句柄
  * @retval 无
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim1)
	{
		DirectBeam_Count++;
	}
}

/**
  * @brief  TIM 满计数中断回调函数
  * @param  htim TIM的句柄
  * @retval 无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim1)
	{
		Angle_Speed = 18 * DirectBeam_Count * 0.017;		//Angle_Speed = rad / T(s)
		DirectBeam_Count = 0;
		Speed = Angle_Speed * 6.6;		//Speed = Angle_Speed * R(cm)
	}
}
