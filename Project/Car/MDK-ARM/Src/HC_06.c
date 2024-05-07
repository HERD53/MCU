#include "gpio.h"
#include "usart.h"
#include "HC_06.h"
#include "OLED.h"
#include "OLED_Data.h"
#include "L298N.h"
#include <string.h>

/**
  ******************************************************************************
  * @file         HC_06.c
  * @brief        该函数用于接收HC-06蓝牙模块数据
  ******************************************************************************
  * @attention		该函数用的是串口1并且开启DMA
	*								波特率：9600
  ******************************************************************************
  */

uint8_t Receive_Data[1];								//串口接收数组
uint8_t Receive_Cache[Receive_Num];			//接收缓存区
uint32_t length;												//接收长度
uint8_t Uart_Receive[Receive_Num];			//将数据传输到外面

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart == &huart1)
	{
		length++;
		Receive_Cache[length - 1] = Receive_Data[0];
		
		if (Receive_Data[0] == 0xFF)				//判断帧尾是否正确
		{
			/* 串口接受逻辑处理开始 */
			if (Receive_Cache[0] == 0x0A)
			{
				L298N_Front(100);
			}
			else if (Receive_Cache[0] == 0x0B)
			{
				L298N_Rear(100);
			}
			else if (Receive_Cache[0] == 0x0C)
			{
				L298N_Left(100);
			}
			else if (Receive_Cache[0] == 0x0D)
			{
				L298N_Right(100);
			}
			else
			{
				L298N_Front(0);
			}
			/* 串口接受逻辑处理结束 */
			memset(Receive_Cache, 0, sizeof(Receive_Cache));
			length = 0;
		}
		
		Receive_Data[0] = 0;
		
		//下方代码需要在初始化时使用
		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, Receive_Data, sizeof(Receive_Data));
		__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
	}
}
