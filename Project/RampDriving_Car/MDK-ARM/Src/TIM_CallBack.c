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
	HAL_TIM_Base_Start_IT(&htim3);
//	HAL_TIM_PWM_Start(&htimX, TIM_CHANNEL_X);
//	HAL_TIM_IC_Start_IT(&htimX, TIM_CHANNEL_X);
//	HAL_TIM_OC_Start_IT(&htimX, TIM_CHANNEL_X);
}

/* Define --------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
float Measured_Speed;

/**
  * @brief  TIM 满计数中断回调函数
  * @param  htim TIM的句柄
  * @retval 无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim3)
	{
		L_Speed = Encoder_Count_L1 / 5.5;
		R_Speed = Encoder_Count_R1 / 5.5;
		Measured_Speed = (L_Speed + R_Speed) / 2.0;
		Encoder_Count_L1 = 0;
		Encoder_Count_R1 = 0;
	}
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
	if (htim == &htim3)
	{
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			Encoder_Count_L1++;
		}
		else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
		{
			Encoder_Count_R1++;
		}
	}
}

/**
  * @brief  TIM PWM中断回调函数
  * @param  htim TIM的句柄
  * @retval 无
  */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	
}
