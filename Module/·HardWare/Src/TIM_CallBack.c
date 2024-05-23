/**
  ******************************************************************************
  * @file         TIM_CallBack.h
  * @brief        定时器回调函数
	*							 This file provides firmware functions to manage the following
	*							 + 将程序写入回调函数中
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* 该文件用到了TIM，需要在STM32CubeMX中配置开启
  ******************************************************************************
  */
	
/* Include -------------------------------------------------------------------*/
#include "main.h"

/* Init ----------------------------------------------------------------------*/
void Tim_Init(void)
{
	/* 按需开启 */
//	HAL_TIM_Base_Start_IT(&htimX);
//	HAL_TIM_PWM_Start(&htimX, TIM_CHANNEL_X);
//	HAL_TIM_IC_Start_IT(&htimX, TIM_CHANNEL_X);
//	HAL_TIM_OC_Start_IT(&htimX, TIM_CHANNEL_X);
}

/* Define --------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/**
  * @brief  TIM 满计数中断回调函数
  * @param  htim TIM的句柄
  * @retval 无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
}

/**
  * @brief  TIM 输出比较中断回调函数
  * @param  htim TIM的句柄
  * @retval 无
  */
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	
}

/**
  * @brief  TIM 输入捕获中断回调函数
  * @param  htim TIM的句柄
  * @retval 无
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	
}

/**
  * @brief  TIM PWM中断回调函数
  * @param  htim TIM的句柄
  * @retval 无
  */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	
}
