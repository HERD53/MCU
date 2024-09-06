/**
  ******************************************************************************
  * @file         Lnfrared_Tracking.c
  * @brief        ����Ѱ��ģ��
	*							 This file provides firmware functions to manage the following
	*							 + ����Ѱ��ģ��Ľ���
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* ���ļ�����GPIO����Ҫ��STM32CubeMX�����ÿ���
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"

/* Init ----------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/
#define GPIOX GPIOB						//GPIOX (X...A,B,C)
#define LEFT_0 GPIO_PIN_7			//��ߵ�һ��������ģ��
#define LEFT_1 GPIO_PIN_6			//��ߵڶ���������ģ��
#define MIDDLE GPIO_PIN_5			//�м������ģ��
#define RIGHT_1 GPIO_PIN_4		//�ұߵڶ���������ģ��
#define RIGHT_0 GPIO_PIN_3		//�ұߵ�һ��������ģ��

/* Variables -----------------------------------------------------------------*/
uint8_t Infrared_state[5];		//�洢����ģ���״̬

/**
  * @brief  ����ѭ��ģ�鷵��ֵ������
  * @param  ��
  * @retval ����ѭ��ģ�鷵��ֵ���飨ʶ�𵽺�����Ϊ0��ûʶ�𵽺���Ϊ1��
  */
uint8_t* Infrared_Judge(void)
{
	for (uint8_t i = 0; i < 7; i++)
	{
		Infrared_state[i] = 0;
	}
	
	if (HAL_GPIO_ReadPin(GPIOX, LEFT_0) == GPIO_PIN_RESET)
	{
		Infrared_state[0] = 1;
	}
	if (HAL_GPIO_ReadPin(GPIOX, LEFT_1) == GPIO_PIN_RESET)
	{
		Infrared_state[1] = 1;
	}
	if (HAL_GPIO_ReadPin(GPIOX, MIDDLE) == GPIO_PIN_RESET)
	{
		Infrared_state[2] = 1;
	}
	if (HAL_GPIO_ReadPin(GPIOX, RIGHT_1) == GPIO_PIN_RESET)
	{
		Infrared_state[3] = 1;
	}
	if (HAL_GPIO_ReadPin(GPIOX, RIGHT_0) == GPIO_PIN_RESET)
	{
		Infrared_state[4] = 1;
	}
	
	return Infrared_state;
}



