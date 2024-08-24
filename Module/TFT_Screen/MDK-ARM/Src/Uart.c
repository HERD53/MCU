/**
  ******************************************************************************
  * @file         Uart.c
  * @brief        
	*							 This file provides firmware functions to manage the following
	*							 + 
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* 
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"
#include <string.h>

/* Define --------------------------------------------------------------------*/
#define Receive_Num 64

/* Variables -----------------------------------------------------------------*/
uint8_t Receive_Data[2];							//接收数组
uint8_t Cache_Data[Receive_Num];			//缓存数组
uint32_t Cache_Count;									//缓存计数

/* Init ----------------------------------------------------------------------*/
void Uart_Init(void)
{
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, Receive_Data, 1);
}

/**
  * @brief  串口发送函数
  * @param  Uart_Data  串口发送数据
  * @retval 无
  */
void Uart_Send(uint8_t Uart_Data)
{
//	uint32_t Size = strlen(Uart_Data);
	uint32_t Size = 1;
	HAL_UART_Transmit(&huart1, &Uart_Data, Size, 0xff);
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
		
		if (Receive_Data[0] == ' ')		//包尾是' '
		{
			/* 用户代码开始 */
			
			/* 用户代码结束 */
			memset(Cache_Data, 0, sizeof(Cache_Data));
			Cache_Count = 0;
		}
	}
	
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, Receive_Data, 1);
}
