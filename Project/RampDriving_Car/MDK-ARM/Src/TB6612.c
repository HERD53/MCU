/**
  ******************************************************************************
  * @file         TB6612.c
  * @brief        �������ģ��
	*							 This file provides firmware functions to manage the following
	*							 + �������
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* 
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"

/* Define --------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/* Init ----------------------------------------------------------------------*/
void Car_Init(void)
{
	HAL_TIM_Base_Start(&htim2);
	
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	
	//��Դ���£��ұ�
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	
	//��Դ���£����
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	
	Car_State = 'S';
	Speed = 0;
}

void Car_Stop(void)
{
	//��Դ���£��ұ� / �����
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	
	//��Դ���£���� / ���ұ�
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
}

void Car_Forward(uint8_t Speed)
{
	//��Դ���£��ұ� / �����
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, Speed);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
	
	//��Դ���£���� / ���ұ�
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, Speed);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}

void Car_Backwards(uint8_t Speed)
{
	//��Դ���£��ұ� / �����
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, Speed);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	
	//��Դ���£���� / ���ұ�
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, Speed);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
}

void Car_Left(uint8_t Speed)
{
	//��Դ���£��ұ� / �����
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, Speed);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
	
	//��Դ���£���� / ���ұ�
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, Speed);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
}

void Car_Right(uint8_t Speed)
{
	//��Դ���£��ұ� / �����
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, Speed);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	
	//��Դ���£���� / ���ұ�
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, Speed);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}
