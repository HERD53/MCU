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
#include <stdio.h>
#include <string.h>

/* Define --------------------------------------------------------------------*/
#define Receive_Num 64							//���������С

/* Variables -----------------------------------------------------------------*/
uint8_t Receive_Data[2];							//��������
uint8_t Cache_Data[Receive_Num];			//��������
uint32_t Cache_Count;									//�������
uint8_t Speed;
uint8_t Car_State;
uint8_t Ctrl_State;

/* Init ----------------------------------------------------------------------*/
void HC06_Init(void)
{
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, Receive_Data, 1);
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
		
		if (Receive_Data[0] == 0x5A)		//��β��' '
		{
			/* �û����뿪ʼ */
			//ң��
			Speed = Cache_Data[2];
			
			if (Cache_Data[1] & 0x01)		//ǰ
			{
				Car_State = 'Q';
			}
			else if (Cache_Data[1] & 0x02)		//��
			{
				Car_State = 'H';
			}
			else if (Cache_Data[1] & 0x04)		//��
			{
				Car_State = 'Z';
			}
			else if (Cache_Data[1] & 0x08)		//��
			{
				Car_State = 'Y';
			}
			else
			{
				Car_State = 'S';
			}
			
			//�Զ�
			Ctrl_State = Cache_Data[3];
			
			/* �û�������� */
			memset(Cache_Data, 0, sizeof(Cache_Data));
			Cache_Count = 0;
		}
	}
	
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, Receive_Data, 1);
}
