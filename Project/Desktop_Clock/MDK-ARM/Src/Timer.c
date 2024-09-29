/**
  ******************************************************************************
  * @file         Timer.c
  * @brief       	定时器驱动
	*							 This file provides firmware functions to manage the following
	*							 + 处理定时器中断的回调函数
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
#define htimX		htim2		//定时器的句柄

/* Variables ------------------------------------------------------------------*/

/* Initialization and de-initialization functions -----------------------------*/
/**
  * @brief  定时器初始化函数
  * @param  无
  * @retval 无
  */
void Timer_Init(void)
{
	HAL_TIM_Base_Start_IT(&htimX);
}

/* Peripheral Control functions -----------------------------------------------*/




