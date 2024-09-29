/**
  ******************************************************************************
  * @file         Uart.c
  * @brief       	��������
	*							 This file provides firmware functions to manage the following
	*							 + ���ڷ���
	*							 + ���ڽ���
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
#define HUARTX		huart1		//���ڵľ��

/* Variables ------------------------------------------------------------------*/
uint8_t Receive_Data[2];					//��������
uint8_t Cache_Data[CACHE_SIZE];		//��������
uint32_t Cache_Count;							//�������
uint8_t Receive_Flag;							//���ձ�־λ

/* Initialization and de-initialization functions -----------------------------*/
/**
  * @brief  ���ڳ�ʼ������
  * @param  ��
  * @retval ��
  */
void Uart_Init(void)
{
	HAL_UARTEx_ReceiveToIdle_IT(&HUARTX, Receive_Data, 1);
}

/* Peripheral Control functions -----------------------------------------------*/
/**
  * @brief  ת����ɻص�����
  * @param  huart ���ڵľ��
  * @retval	Size  Ӧ�ó�����ջ������п��õ�������
  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart == &HUARTX)		//��ֹ���������󴥷�
	{
		Cache_Data[Cache_Count] = Receive_Data[0];
		Cache_Count++;
		
		if (Receive_Data[0] == '}')		//�������һλΪ}
		{
			if (!My_Strcmp((char*)Cache_Data, ">{\"success\"", 11))			//�ж��Ƿ��ǶԵ�����
			{
				sprintf(Time_Receive, "%s", (Cache_Data + 65));						//ƫ��65���ֽھ���ʱ�����ݵ�λ��
			}
			memset(Cache_Data, 0, sizeof(Cache_Data));
			Cache_Count = 0;
		}
		
		if ((Receive_Data[0] == '\n') && (Receive_Flag >= 1))		//�������һλΪ\n��Receive_Flag��Ϊ���ҵ����������м��OK
		{
			Receive_Flag = 0;
			/* �û����뿪ʼ */
			if (!My_Strcmp((char*)Cache_Data, "OK", 2))
			{
				OK_Flag = 1;
			}
			/* �û�������� */
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
  * @brief  �Լ�д��strcmp
  * @param  Str1    �ַ���1
  * @param  Str2    �ַ���2
  * @param  Length  һ���ĳ���
  * @retval �Ƿ���ͬ����ͬ0����ͬ1
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



