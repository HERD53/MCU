/**
  ******************************************************************************
  * @file         HC_SR04.h
  * @brief        ������ģ��
	*							 This file provides firmware functions to manage the following
	*							 + ���������
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* ���ļ�����GPIO��TIM\���벶����Ҫ��STM32CubeMX�����ÿ���
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"

/* Init ----------------------------------------------------------------------*/
void HCSR04_Init(void)
{
	HAL_TIM_IC_Start_IT(&htimX, TIM_CHANNEL_X);
}

/* Define --------------------------------------------------------------------*/
#define GPIOX GPIOA
#define GPIO_PIN_X GPIO_PIN_1

/* Variables -----------------------------------------------------------------*/
uint32_t Ultrasonic_Start;
uint32_t Ultrasonic_Stop;

/**
  * @brief  ���������
  * @param  ��
  * @retval ��
  */
uint32_t Ultrasonic_Ranging(void)
{
	uint32_t val;
	
	HAL_GPIO_WritePin(GPIOX, GPIO_PIN_X, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOX, GPIO_PIN_X, GPIO_PIN_RESET);
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	HAL_Delay(20);
	
	val = ((Ultrasonic_Stop - Ultrasonic_Start) * 0.034) / 2;		//��λ��cm
	return val;
}

/**
  * @brief  TIM ���벶���жϻص�����
  * @param  htim TIM�ľ��
  * @retval ��
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim2)
	{
		Ultrasonic_Start = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		Ultrasonic_Stop = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
	}
}
