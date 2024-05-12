#include "main.h"
#include "Lnfrared_Tracking.h"

/**
  ******************************************************************************
  * @file         Lnfrared_Tracking.c
  * @brief        红外寻迹模块
	*							 This file provides firmware functions to manage the following
	*							 + 红外寻迹模块的接收
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* 该文件包含GPIO，需要在STM32CubeMX中配置开启
  ******************************************************************************
  */

uint8_t Infrared_state[5];		//存储红外模块的状态

/**
  * @brief  红外循迹模块返回值处理函数
  * @param  无
  * @retval 红外循迹模块返回值数组
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



