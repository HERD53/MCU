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
void Encoder_Init(void)
{
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);
}

/* Define --------------------------------------------------------------------*/
//��Դ���£�����
#define GPIO_PIN_LA GPIO_PIN_0
#define GPIO_PIN_LB GPIO_PIN_1
#define GPIO_PIN_RA GPIO_PIN_6
#define GPIO_PIN_RB GPIO_PIN_7

/* Variables -----------------------------------------------------------------*/
uint32_t Encoder_Count_L1;
uint32_t Encoder_Count_L2;
uint32_t Encoder_Count_R1;
uint32_t Encoder_Count_R2;
float L_Speed;
float R_Speed;

/**
  * @brief  TIM ���벶���жϻص�����
  * @param  htim TIM�ľ��
  * @retval ��
  */
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
//{
//	if (htim == &htim3)
//	{
//		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
//		{
//			Encoder_Count_L1++;
//		}
//		else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
//		{
//			Encoder_Count_R1++;
//		}
//	}
//}
