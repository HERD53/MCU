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
	* 该文件包含USART、DMA、OLED，需要在STM32CubeMX中配置开启
	* OLED需要配置好SCL、SDA为开漏输出进行IIC通信
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include <string.h>

/* Define --------------------------------------------------------------------*/
#define Receive_Num 64							//缓存数组大小

/* Variables -----------------------------------------------------------------*/
uint8_t Receive_Data[2];							//接收数组
uint8_t Cache_Data[Receive_Num];			//缓存数组
uint32_t Cache_Count;									//缓存计数
uint8_t Speed;
uint8_t Car_State;
uint8_t Ctrl_State;

/* Init ----------------------------------------------------------------------*/
void HC06_Init(void)
{
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, Receive_Data, 1);
}

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
		
		if (Receive_Data[0] == 0x5A)		//包尾是' '
		{
			/* 用户代码开始 */
			//遥控
			Speed = Cache_Data[2];
			
			if (Cache_Data[1] & 0x01)		//前
			{
				Car_State = 'Q';
			}
			else if (Cache_Data[1] & 0x02)		//后
			{
				Car_State = 'H';
			}
			else if (Cache_Data[1] & 0x04)		//左
			{
				Car_State = 'Z';
			}
			else if (Cache_Data[1] & 0x08)		//右
			{
				Car_State = 'Y';
			}
			else
			{
				Car_State = 'S';
			}
			
			//自动
			Ctrl_State = Cache_Data[3];
			
			/* 用户代码结束 */
			memset(Cache_Data, 0, sizeof(Cache_Data));
			Cache_Count = 0;
		}
	}
	
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, Receive_Data, 1);
}
