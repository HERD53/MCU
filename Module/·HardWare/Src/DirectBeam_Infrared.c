/**
  ******************************************************************************
  * @file         DirectBeam_Infrared.c
  * @brief        ����ʽ����ģ��
	*							 This file provides firmware functions to manage the following
	*							 + ������ʽ����ģ�鱻�ڵ��Ĵ���
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* ���ļ�����TIM\���벶����Ҫ��STM32CubeMX�����ÿ���
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
  * @brief  TIM ���벶���жϻص�����
  * @param  htim TIM�ľ��
  * @retval ��
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim2)
	{
		DirectBeam_Count++;
	}
}
