/**
  ******************************************************************************
  * @file         Uart.c
  * @brief       	串口驱动
	*							 This file provides firmware functions to manage the following
	*							 + 串口发送
	*							 + 串口接收
  ******************************************************************************
  * @attention		
	*	
	*	The required HAL header files such as gpio.h are included in main.h
	* 
  ******************************************************************************
  */

/* Include --------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include "string.h"

/* Define ---------------------------------------------------------------------*/
#define HUARTX		huart1		//串口的句柄

/* Variables ------------------------------------------------------------------*/
uint8_t Receive_Data[2];					//接收数组
uint8_t Cache_Data[CACHE_SIZE];		//缓存数组
uint32_t Cache_Count;							//缓存计数
uint8_t Receive_Flag;							//接收标志位

/* Initialization and de-initialization functions -----------------------------*/
/**
  * @brief  串口初始化函数
  * @param  无
  * @retval 无
  */
void Uart_Init(void)
{
	HAL_UARTEx_ReceiveToIdle_IT(&HUARTX, Receive_Data, 1);
}

/* Peripheral Control functions -----------------------------------------------*/
/**
  * @brief  转移完成回调函数
  * @param  huart 串口的句柄
  * @retval	Size  应用程序接收缓冲区中可用的数据数
  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart == &HUARTX)		//防止其他串口误触发
	{
		Cache_Data[Cache_Count] = Receive_Data[0];
		Cache_Count++;
		
		if (Receive_Data[0] == '}')		//数据最后一位为}
		{
			if (!My_Strcmp((char*)Cache_Data, ">{\"success\"", 11))			//判断是否是对的数据
			{
				sprintf(Time_Receive, "%s", (Cache_Data + 65));						//偏移65个字节就是时间数据的位置
			}
			memset(Cache_Data, 0, sizeof(Cache_Data));
			Cache_Count = 0;
		}
		
		if ((Receive_Data[0] == '\n') && (Receive_Flag >= 1))		//数据最后一位为\n，Receive_Flag是为了找到两个换行中间的OK
		{
			Receive_Flag = 0;
			/* 用户代码开始 */
			if (!My_Strcmp((char*)Cache_Data, "OK", 2))
			{
				OK_Flag = 1;
			}
			/* 用户代码结束 */
			memset(Cache_Data, 0, sizeof(Cache_Data));
			Cache_Count = 0;
		}
		
		if (Receive_Data[0] == '\n')
		{
			Receive_Flag++;
			memset(Cache_Data, 0, sizeof(Cache_Data));
			Cache_Count = 0;
		}
	}
	
	HAL_UARTEx_ReceiveToIdle_IT(&HUARTX, Receive_Data, 1);
}

/**
  * @brief  自己写的strcmp
  * @param  Str1    字符串1
  * @param  Str2    字符串2
  * @param  Length  一样的长度
  * @retval 是否相同，相同0，不同1
  */
uint8_t My_Strcmp(const char* Str1, const char* Str2, uint8_t Length)
{
	uint32_t count = 0;
	
	for (uint32_t i = 0; i < Length; i++)
	{
		if (Str1[i] == Str2[i])
		{
			count++;
		}
	}
	
	if (count == Length)
	{
		return 0;
	}
	
	return 1;
}



