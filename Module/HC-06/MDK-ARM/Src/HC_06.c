#include "main.h"
#include "HC_06.h"
#include "OLED.h"
#include "OLED_Data.h"
#include <string.h>

/**
  ******************************************************************************
  * @file         HC-06.h
  * @brief				蓝牙模块
	*							 This file provides firmware functions to manage the following
	*							 + 蓝牙发送
	*							 + 蓝牙接收
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* 该文件用到了USART、DMA、OLED，需要在STM32CubeMX中配置开启
	* OLED需要配置好SCL、SDA为开漏输出进行IIC通信
  ******************************************************************************
  */

uint8_t Receive_Data[2];							//接收数组
uint8_t Cache_Data[Receive_Num];			//缓存数组
uint32_t Cache_Count;									//缓存计数

/**
  * @brief  串口中断函数的回调函数
  * @param  huart  串口的句柄
	* @param  Size  接收到的数据大小
  * @retval 无
  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart == &huart1)		//防止其他串口触发
	{
		Cache_Data[Cache_Count] = Receive_Data[0];
		Cache_Count++;
		
		if (Receive_Data[0] == ' ')		//包尾是' '
		{
			/* 用户代码开始 */
			
			/* 用户代码结束 */
			memset(Cache_Data, 0, sizeof(Cache_Data));
			Cache_Count = 0;
		}
	}
	
	//以下代码要用于初始化
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, Receive_Data, 1);
}
