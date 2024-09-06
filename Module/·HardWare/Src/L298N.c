/**
  ******************************************************************************
  * @file         L298N.c
  * @brief        �������ģ��
	*							 This file provides firmware functions to manage the following
	*							 + �������
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* ���ļ�����TIM����Ҫ��STM32CubeMX�����ÿ���
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"

/* Init ----------------------------------------------------------------------*/
void Car_Init(void)
{
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_Base_Start(&htim3);
	
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 0);
	
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, 0);
}

/* Define --------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

void Car_Forward(uint8_t Speed)
{
	//��ǰ��
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, Speed);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 0);
	//�����
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, Speed);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 0);
	//��ǰ��
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, Speed);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, 0);
	//�Һ���
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, Speed);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
}

void Car_Backwards(uint8_t Speed)
{
	//��ǰ��
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, Speed);
	//�����
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, Speed);
	//��ǰ��
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, Speed);
	//�Һ���
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, Speed);
}

void Car_Left(uint8_t Speed)
{
	//��ǰ��
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, Speed);
	//�����
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, Speed);
	//��ǰ��
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, Speed);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, 0);
	//�Һ���
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, Speed);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
}

void Car_Light(uint8_t Speed)
{
	//��ǰ��
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, Speed);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 0);
	//�����
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, Speed);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 0);
	//��ǰ��
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, Speed);
	//�Һ���
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 0);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, Speed);
}
