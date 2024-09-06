/**
  ******************************************************************************
  * @file         TIM_CallBack.h
  * @brief        ��ʱ���ص�����
	*							 This file provides firmware functions to manage the following
	*							 + ������д��ص�������
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* ���ļ��õ���TIM����Ҫ��STM32CubeMX�����ÿ���
  ******************************************************************************
  */
	
/* Include -------------------------------------------------------------------*/
#include "main.h"

/* Init ----------------------------------------------------------------------*/
void Tim_Init(void)
{
	/* ���迪�� */
	HAL_TIM_Base_Start_IT(&htim3);
//	HAL_TIM_PWM_Start(&htimX, TIM_CHANNEL_X);
//	HAL_TIM_IC_Start_IT(&htimX, TIM_CHANNEL_X);
//	HAL_TIM_OC_Start_IT(&htimX, TIM_CHANNEL_X);
}

/* Define --------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
float Measured_Speed;

/**
  * @brief  TIM �������жϻص�����
  * @param  htim TIM�ľ��
  * @retval ��
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
  * @brief  TIM ����Ƚ��жϻص�����
  * @param  htim TIM�ľ��
  * @retval ��
  */
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	
}

/**
  * @brief  TIM ���벶���жϻص�����
  * @param  htim TIM�ľ��
  * @retval ��
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
  * @brief  TIM PWM�жϻص�����
  * @param  htim TIM�ľ��
  * @retval ��
  */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	
}
