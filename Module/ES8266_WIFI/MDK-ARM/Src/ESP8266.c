/**
  ******************************************************************************
  * @file         ESP8266.c
  * @brief       	ESP8266����
	*							 This file provides firmware functions to manage the following
	*							 + ESP8266ʹ��ATָ���������
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
#define GPIO_RST				GPIOA					//��λ GPIOX
#define GPIO_PIN_RST		GPIO_PIN_0		//��λ GPIO_PIN_X
#define WAITING_TIME		6000					//�ȴ�ʱ��(MS)

/* Variables ------------------------------------------------------------------*/
volatile uint8_t OK_Flag;									//�ж�ATָ���Ƿ񷵻�OK��־λ
Command_ErrorTypeDef Error_Cmd;							//����ָ���
volatile uint32_t Error_Time;							//����ʱʱ��(ms)
char Time_Receive[TIME_RECEIVE_SIZE];		//�洢ʱ������
char Time_YMD[11] = { 0 };									//ʱ��(������)����ʽ(xxxx-xx-xx)
char Time_HMS[9] = { 0 };										//ʱ��(ʱ����)����ʽ(xx:xx:xx)

/* Initialization and de-initialization functions -----------------------------*/

/* Peripheral Control functions -----------------------------------------------*/
/**
  * @brief  ATָ��ͺ���
  * @param  Command  Ҫ���͵�ATָ��
  * @param  Send_Num ��������ʱ���ַ�������
  * @retval ��
  */
void AT_Send(char* Command, Command_StateTypeDef State)
{
	uint8_t Cmd[200] = { 0 };
	Error_Time = 0;		//��ʱʱ�����
	
	if (!strcmp(Command, AT_CONNECT_WIFI))		//����ָ�� AT_CONNECT_WIFI
	{
		Error_Cmd = AT_WIFI_ERROR;
		sprintf((char *)Cmd, "%s\"%s\",\"%s\"\r\n", Command, WIFI_ACCOUNT, WIFI_PASSWORD);
		HAL_UART_Transmit(&huart1, Cmd, sizeof(Cmd), 0xff);
	}
	else if (!strcmp(Command, AT_CONNECT_SERVER))		//����ָ�� AT_CONNECT_SERVER
	{
		Error_Cmd = AT_SERVER_ERROR;
		if (State == HOME_SERVER_STATE)		//�뱾��TCP����������
		{
			sprintf((char *)Cmd, "%s\"TCP\",\"%s\",%s\r\n", Command, SERVER_IP, SERVER_PORT_NUM);
		}
		else if (State == REMOTE_SERVER_STATE)		//��Զ��TCP����������
		{
			sprintf((char *)Cmd, "%s\"TCP\",\"%s\",%s\r\n", Command, SERVER_URL, SERVER_TCP);
		}
		HAL_UART_Transmit(&huart1, Cmd, sizeof(Cmd), 0xff);
	}
	else if (State == SEND_DATA_STATE)		//��������
	{
		Error_Cmd = AT_SEND_ERROR;
		sprintf((char *)Cmd, "%s", Command);
		HAL_UART_Transmit(&huart1, Cmd, sizeof(Cmd), 0xff);
		Error_Time = WAITING_TIME - 1000;		//�ȴ�1000(ms)
	}
	else if (State == AT_CIPSEND_STATE)		//����ָ�� AT_CIPSEND
	{
		sprintf((char *)Cmd, "%s", Command);
		HAL_UART_Transmit(&huart1, Cmd, 12, 0xff);
	}
	else
	{
		sprintf((char *)Cmd, "%s", Command);
		HAL_UART_Transmit(&huart1, Cmd, sizeof(Cmd), 0xff);
	}
	
	while (!OK_Flag)
	{
		if (Error_Time >= WAITING_TIME)		//��ʱʱ������ΪWAITING_TIME(MS)
		{
			break;		//��ʱֱ����һ��ָ��
			//��������ʱ��ʹ��(ʹ��ʱҪ�������breakɾ��)
			if (Error_Cmd == AT_WIFI_ERROR)
			{
				
			}
			else if (Error_Cmd == AT_SERVER_ERROR)
			{
				
			}
			else if (Error_Cmd == AT_TIME_ERROR)
			{
				
			}
			else if (Error_Cmd == AT_SEND_ERROR)
			{
				
			}
		}
	}
	OK_Flag = 0;						//�������OK��־λ
	Error_Cmd = NO_ERROR;		//�������״̬
}

/**
  * @brief  �˳�͸��ģʽ
  * @param  ��
  * @retval ��
  */
void Exit_CIPMODE_1(void)
{
	HAL_Delay(50);
	HAL_UART_Transmit(&huart1, "+++", 3, 0xff);
}

/**
  * @brief  ESP8266��ʼ������
  * @param  ��
  * @retval ��
  */
void ESP8266_Init(void)
{
	ESP8266_RST();																			//��ʼ��
	AT_Send(AT_STA, NO_STATE);													//����ΪSTAģʽ
	AT_Send(AT_CONNECT_WIFI, NO_STATE);									//����WIFI
	AT_Send(AT_CONNECT_SERVER, REMOTE_SERVER_STATE);		//���ӷ�����
	AT_Send(AT_CIPMODE_1, NO_STATE);										//��͸��ģʽ
}

/**
  * @brief  ESP8266�����ַ�������
  * @param  String ���͵�����
  * @retval ��
  */
void ESP8266_SendString(char* String)
{
	AT_Send(AT_CIPSEND, AT_CIPSEND_STATE);
	AT_Send(String, SEND_DATA_STATE);
}

/**
  * @brief  ESP8266��λ����
  * @param  ��
  * @retval ��
  */
void ESP8266_RST(void)
{
	HAL_GPIO_WritePin(GPIO_RST, GPIO_PIN_RST, GPIO_PIN_RESET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIO_RST, GPIO_PIN_RST, GPIO_PIN_SET);
}

/**
  * @brief  ESP8266��ȡʱ�亯��
  * @param  ��
  * @retval ��
  */
void ESP8266_GetTime(void)
{
	//��д��Ӧ��appkey=��&sign=��
	ESP8266_SendString("GET http://api.k780.com:88/?app=life.time&appkey=74037&sign=c9228380d8d43a8b696406c77902ca87&format=json&HTTP/1.1\r\n");		//��д��Ӧ��appkey=��&sign=��
	Exit_CIPMODE_1();
	Time_Receive[10] = '\0';
	Time_Receive[19] = '\0';
	String_Copy(Time_YMD, Time_Receive, 10);
	String_Copy(Time_HMS, (Time_Receive + 11), 8);
	OLED_ShowString(0, 0, Time_YMD, 8);
	OLED_ShowString(0, 16, Time_HMS, 8);
	OLED_Update();
}

/**
  * @brief  �ַ������ƺ���
  * @param  Str1    �ַ���1
  * @param  Str2    �ַ���2
  * @param  Length  Ҫ���Ƶĳ���
  * @retval ��
  */
void String_Copy(char* Str1, char* Str2, uint16_t Length)
{
	for (uint8_t i = 0; i < Length; i++)
	{
		Str1[i] = Str2[i];
	}
}



