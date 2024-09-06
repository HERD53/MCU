/**
  ******************************************************************************
  * @file         HC-06.h
  * @brief				����ģ��
	*							 This file provides firmware functions to manage the following
	*							 + ��������
	*							 + ��������
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* ���ļ�����USART��DMA��OLED����Ҫ��STM32CubeMX�����ÿ���
	* OLED��Ҫ���ú�SCL��SDAΪ��©�������IICͨ��
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"
#include <string.h>

/* Define --------------------------------------------------------------------*/
#define Receive_Num 64							//���������С

/* Variables -----------------------------------------------------------------*/
uint8_t Receive_Data[2];							//��������
uint8_t Cache_Data[Receive_Num];			//��������
uint32_t Cache_Count;									//�������

/* Init ----------------------------------------------------------------------*/
void HC06_Init(void)
{
	HAL_UARTEx_ReceiveToIdle_IT(&huartX, Receive_Data, 1);
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
