/**
  ******************************************************************************
  * @file         Timer.c
  * @brief       	��ʱ������
	*							 This file provides firmware functions to manage the following
	*							 + ����ʱ���жϵĻص�����
  ******************************************************************************
  * @attention		
	*	
	*	The required HAL header files such as gpio.h are included in main.h
	* 
  ******************************************************************************
  */

/* Include --------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

/* Define ---------------------------------------------------------------------*/
#define htimX		htim2		//��ʱ���ľ��

/* Variables ------------------------------------------------------------------*/

/* Initialization and de-initialization functions -----------------------------*/
/**
  * @brief  ��ʱ����ʼ������
  * @param  ��
  * @retval ��
  */
void Timer_Init(void)
{
	HAL_TIM_Base_Start_IT(&htimX);
}

/* Peripheral Control functions -----------------------------------------------*/




