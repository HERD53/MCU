#include "main.h"

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
