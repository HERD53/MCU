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
uint8_t Receive_Data[2];							//��������
uint8_t Cache_Data[Receive_Num];			//��������
uint32_t Cache_Count;									//�������

/* Init ----------------------------------------------------------------------*/
void Uart_Init(void)
{
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, Receive_Data, 1);
}

/**
  * @brief  ���ڷ��ͺ���
  * @param  Uart_Data  ���ڷ�������
  * @retval ��
  */
void Uart_Send(uint8_t Uart_Data)
{
//	uint32_t Size = strlen(Uart_Data);
	uint32_t Size = 1;
	HAL_UART_Transmit(&huart1, &Uart_Data, Size, 0xff);
}

/**
  * @brief  �����жϺ����Ļص�����
  * @param  huart  ���ڵľ��
	* @param  Size  ���յ������ݴ�С
  * @retval ��
  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart == &huart1)		//��ֹ�������ڴ���
	{
		Cache_Data[Cache_Count] = Receive_Data[0];
		Cache_Count++;
		
		if (Receive_Data[0] == ' ')		//��β��' '
		{
			/* �û����뿪ʼ */
			
			/* �û�������� */
			memset(Cache_Data, 0, sizeof(Cache_Data));
			Cache_Count = 0;
		}
	}
	
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, Receive_Data, 1);
}
