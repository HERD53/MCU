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
	HAL_TIM_IC_Start_IT(&htimX, TIM_CHANNEL_X);
}

/* Define --------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
uint32_t DirectBeam_Count;

/**
  * @brief  TIM 输入捕获中断回调函数
  * @param  htim TIM的句柄
  * @retval 无
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim2)
	{
		DirectBeam_Count++;
	}
}
