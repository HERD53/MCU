#include "main.h"
#include "Key.h"

/**
  ******************************************************************************
  * @file         Key.c
  * @brief        按键模块
	*							 This file provides firmware functions to manage the following
	*							 + 检测按键是否按下
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	*	该文件包含GPIO、EXTI、TIM，需要在STM32CubeMX中配置开启
  ******************************************************************************
  */

uint32_t Key_Count;			//检测长按计数
uint8_t Key_Tim_Flag;		//按键长按标志位
uint8_t Key_Flag;				//按键长按标志位

/**
  * @brief  按键检测模块
  * @param  无
  * @retval 无
  */
void Key_LongPress(void)
{
	if (HAL_GPIO_ReadPin(GPIOX, GPIO_PIN_X) == GPIO_PIN_SET)
	{
		/* 按下按键 */
		Key_Tim_Flag = 1;
		/* 用户代码开始 */
		
		/* 用户代码结束 */
	}
	else
	{
		/* 松开按键 */
		Key_Tim_Flag = 0;
		/* 用户代码开始 */
		
		/* 用户代码结束 */
	}
}

/**
  * @brief  TIM中断回调函数
  * @param  htim TIM的句柄
  * @retval 无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim2)		//防止其他定时器触发
	{
		if (Key_Tim_Flag)
		{
			/* 长按按下 */
			Key_Count++;
			if (Key_Count == 1000)		//定时器中断1ms进入时，为定时1000ms
			{
				/* 计数满足 */
				Key_Count = 0;		//计数清空
				Key_Flag = 1;			//其他函数可以检测这个变量，达到长按触发其他函数
				/* 用户代码开始 */
				
				/* 用户代码结束 */
			}
		}
		else
		{
			/* 长按松开 */
			Key_Count = 0;		//防止松开后再次长按的时间不是设定值
			/* 用户代码开始 */
			
			/* 用户代码结束 */
		}
	}
}

/**
  * @brief  EXTI中断回调函数
  * @param  GPIO_Pin GPIO的引脚
  * @retval 无
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_X)		//防止其他GPIO引脚触发
	{
		uint32_t num = 120000;
		while (num--);
		if (HAL_GPIO_ReadPin(GPIOX, GPIO_PIN_X) == GPIO_PIN_SET)		//防止抖动
		{
			Key_Tim_Flag = 1;
			/* 用户代码开始 */
			
			/* 用户代码结束 */
		}
		else
		{
			Key_Tim_Flag = 0;
			/* 用户代码开始 */
			
			/* 用户代码结束 */
		}
	}
}
