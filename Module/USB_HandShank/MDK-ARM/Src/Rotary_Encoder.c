/**
  ******************************************************************************
  * @file         Rotary_Encoder.c
  * @brief        旋转编码器模块
	*							 This file provides firmware functions to manage the following
	*							 + 检测旋转编码器方向、速度以及加速度
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
void Encoder_Init(void)
{
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);      //开启编码器定时器
  __HAL_TIM_ENABLE_IT(&htim1,TIM_IT_UPDATE);
	__HAL_TIM_SET_COUNTER(&htim1, 10000);
//	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
//	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);
}

/* Define --------------------------------------------------------------------*/
#define GPIOX GPIOA
#define GPIO_PIN_A GPIO_PIN_8
#define GPIO_PIN_B GPIO_PIN_9
#define COUNTERNUM __HAL_TIM_GetCounter(&htim1)        //获取编码器定时器中的计数值

/* Variables -----------------------------------------------------------------*/
int32_t Rotary_Encoder_Count;
int8_t Degree;

/**
  * @brief  旋转编码器检测
  * @param  无
  * @retval 旋转的格数
  */
uint32_t Encoder_Detection(void)
{
	if (Rotary_Encoder_Count % 2)
	{
		Rotary_Encoder_Count--;
	}
	
	if (Rotary_Encoder_Count >= 40)
	{
		return 0;
	}
	else if (Rotary_Encoder_Count <= -40)
	{
		return 0;
	}
	
	Degree = Rotary_Encoder_Count * 3;
}

/**
  * @brief  TIM 输入捕获中断回调函数
  * @param  htim TIM的句柄
  * @retval 无
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if ((htim == &htim1) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1))
	{
		if (HAL_GPIO_ReadPin(GPIOX, GPIO_PIN_B) == GPIO_PIN_RESET)
		{
			Rotary_Encoder_Count++;
		}
		else
		{
			Rotary_Encoder_Count--;
		}
	}
//	else if ((htim == &htim1) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2))
//	{
//		if (HAL_GPIO_ReadPin(GPIOX, GPIO_PIN_A) == GPIO_PIN_RESET)
//		{
//			Rotary_Encoder_Count++;
//		}
//		else
//		{
//			Rotary_Encoder_Count--;
//		}
//	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  //如果是编码器更新中断,即10ms内,脉冲数超过了计数范围,需要进行处理
	if (htim->Instance == htim1.Instance)
	{
		if(COUNTERNUM < 10000)	Rotary_Encoder_Count++;         //向上计数超过10000，正溢出+1
		else if(COUNTERNUM > 10000)	Rotary_Encoder_Count--;     //向下计数小于0，负溢出+1
		__HAL_TIM_SetCounter(&htim1, 10000);            				//重新设定初始值			
	}
}