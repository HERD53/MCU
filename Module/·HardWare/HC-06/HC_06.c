#include "gpio.h"
#include "usart.h"
#include "HC_06.h"
#include "OLED.h"
#include "OLED_Data.h"
#include <string.h>

uint8_t Receive_Data[1];
uint8_t Uart_Receive[Receive_Num];
uint32_t length;

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart == &huart1)
	{
		length++;
		Uart_Receive[length - 1] = Receive_Data[0];
		
		if (Receive_Data[0] == 0x0D)
		{
			/* 串口接受逻辑处理开始 */
			
			/* 串口接受逻辑处理结束 */
			memset(Uart_Receive, 0, sizeof(Uart_Receive));
			length = 0;
		}
		
		Receive_Data[0] = 0;
		
		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, Receive_Data, sizeof(Receive_Data));
		__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
	}
}
