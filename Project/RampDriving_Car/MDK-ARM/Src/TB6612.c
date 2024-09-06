/**
  ******************************************************************************
  * @file         TB6612.c
  * @brief        电机驱动模块
	*							 This file provides firmware functions to manage the following
	*							 + 驱动电机
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
	
	//电源在下，右边
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	
	//电源在下，左边
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	
	Car_State = 'S';
	Speed = 0;
}

void Car_Stop(void)
{
	//电源在下，右边 / 车左边
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	
	//电源在下，左边 / 车右边
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
}

void Car_Forward(uint8_t Speed)
{
	//电源在下，右边 / 车左边
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, Speed);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
	
	//电源在下，左边 / 车右边
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, Speed);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}

void Car_Backwards(uint8_t Speed)
{
	//电源在下，右边 / 车左边
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, Speed);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	
	//电源在下，左边 / 车右边
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, Speed);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
}

void Car_Left(uint8_t Speed)
{
	//电源在下，右边 / 车左边
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, Speed);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
	
	//电源在下，左边 / 车右边
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, Speed);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
}

void Car_Right(uint8_t Speed)
{
	//电源在下，右边 / 车左边
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, Speed);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	
	//电源在下，左边 / 车右边
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, Speed);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}
