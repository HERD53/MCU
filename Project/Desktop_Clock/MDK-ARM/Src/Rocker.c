/**
  ******************************************************************************
  * @file         Rocker.c
  * @brief       	遥杆控制驱动
	*							 This file provides firmware functions to manage the following
	*							 + 接收摇杆信息
  ******************************************************************************
  * @attention		
	*	
	*	The required HAL header files such as gpio.h are included in main.h
	* 
  ******************************************************************************
  */

/* Include --------------------------------------------------------------------*/
#include "main.h"

/* Define ---------------------------------------------------------------------*/
#define ADC_VALSIZE		2

/* Variables ------------------------------------------------------------------*/
uint16_t ADC_Value[ADC_VALSIZE];
RockerDirectionTypeDef RockerUD;		// 上下
RockerDirectionTypeDef RockerLR;		// 左右

/* Initialization and de-initialization functions -----------------------------*/

/* Peripheral Control functions -----------------------------------------------*/
/**
  * @brief  ADC初始化函数
  * @param  无
  * @retval 无
  */
void RockerADC_Init(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC_Value, ADC_VALSIZE);
}

/**
  * @brief  ADC转换完成中断回调函数
  * @param  hadc ADC的句柄
  * @retval 无
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if (hadc->Instance == ADC1)
	{
		if (ADC_Value[1] > 3000)
		{
			RockerUD = DOWN;
		}
		else if (ADC_Value[1] < 900)
		{
			RockerUD = UP;
		}
		else
		{
			RockerUD = MIDDLE;
		}
		
		if (ADC_Value[0] > 3000)
		{
			RockerLR = LEFT;
		}
		else if (ADC_Value[0] < 900)
		{
			RockerLR = RIGHT;
		}
		else
		{
			RockerLR = MIDDLE;
		}
	}
}

