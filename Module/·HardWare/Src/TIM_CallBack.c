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
//	HAL_TIM_Base_Start_IT(&htimX);
//	HAL_TIM_PWM_Start(&htimX, TIM_CHANNEL_X);
//	HAL_TIM_IC_Start_IT(&htimX, TIM_CHANNEL_X);
//	HAL_TIM_OC_Start_IT(&htimX, TIM_CHANNEL_X);
}

/* Define --------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/**
  * @brief  TIM �������жϻص�����
  * @param  htim TIM�ľ��
  * @retval ��
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
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
	
}

/**
  * @brief  TIM PWM�жϻص�����
  * @param  htim TIM�ľ��
  * @retval ��
  */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	
}
