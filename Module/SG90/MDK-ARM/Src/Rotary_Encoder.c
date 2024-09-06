/**
  ******************************************************************************
  * @file         Rotary_Encoder.c
  * @brief        ��ת������ģ��
	*							 This file provides firmware functions to manage the following
	*							 + �����ת�����������ٶ��Լ����ٶ�
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
//HAL_TIM_IC_Start_IT(&htimX, TIM_CHANNEL_X);

/* Define --------------------------------------------------------------------*/
#define GPIOX GPIOA
#define GPIO_PIN_A GPIO_PIN_6
#define GPIO_PIN_B GPIO_PIN_7

/* Variables -----------------------------------------------------------------*/
int32_t Rotary_Encoder_Count = 45;

/**
  * @brief  ��ת���������
  * @param  ��
  * @retval ��ת�ĸ���
  */
uint32_t Encoder_Detection(void)
{
	
}

/**
  * @brief  TIM ���벶���жϻص�����
  * @param  htim TIM�ľ��
  * @retval ��
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		if (HAL_GPIO_ReadPin(GPIOX, GPIO_PIN_B) == GPIO_PIN_SET)
		{
			Rotary_Encoder_Count++;
		}
		else
		{
			Rotary_Encoder_Count--;
		}
	}
	else if (htim == &htim3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
	{
		if (HAL_GPIO_ReadPin(GPIOX, GPIO_PIN_A) == GPIO_PIN_RESET)
		{
			Rotary_Encoder_Count++;
		}
		else
		{
			Rotary_Encoder_Count--;
		}
	}
}
