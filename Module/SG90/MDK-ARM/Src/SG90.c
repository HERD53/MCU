/**
  ******************************************************************************
  * @file         SG90.h
  * @brief        ���ģ��
	*							 This file provides firmware functions to manage the following
	*							 + ���ƶ��
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* ���ļ�����TIM\PWM����Ҫ��STM32CubeMX�����ÿ���
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"
#include "SG90.h"

/* Init ----------------------------------------------------------------------*/
//HAL_TIM_PWM_Start(&htimX, TIM_CHANNEL_X);

/* Define --------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/**
  * @brief  �������
  * @param  Angle �����ת�ĽǶ�
  * @retval ��
  */
void SteeringEngine_Control(uint32_t TIM_CHANNEL, uint8_t Angle)
{
	uint32_t temp;
	temp = ((Angle * 12) / 18) + 30;
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL, temp);
}
