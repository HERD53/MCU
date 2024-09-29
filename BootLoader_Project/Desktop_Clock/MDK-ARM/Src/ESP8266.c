/**
  ******************************************************************************
  * @file         ESP8266.c
  * @brief       	ESP8266驱动
	*							 This file provides firmware functions to manage the following
	*							 + ESP8266使用AT指令进行配网
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
#define GPIO_RST				GPIOA					//复位 GPIOX
#define GPIO_PIN_RST		GPIO_PIN_0		//复位 GPIO_PIN_X
#define WAITING_TIME		6000					//等待时间(MS)

/* Variables ------------------------------------------------------------------*/
volatile uint8_t OK_Flag;													//判断AT指令是否返回OK标志位
Command_ErrorTypeDef Error_Cmd;											//错误指令号
volatile uint32_t Error_Time;											//错误超时时间(ms)
uint8_t ErrorSkip_Flag = 0;													//错误跳过标志位
char Time_Receive[TIME_RECEIVE_SIZE] = { 0 };				//存储时间数组
char Time_Transition[30] = { 0 };										//存储时间数组
char Time_YMD[11] = { 0 };													//时间(年月日)；格式(xxxx-xx-xx)
char Time_HMS[9] = { 0 };														//时间(时分秒)；格式(xx:xx:xx)
uint16_t Time_Count;

/* Initialization and de-initialization functions -----------------------------*/

/* Peripheral Control functions -----------------------------------------------*/
/**
  * @brief  AT指令发送函数
  * @param  Command  要发送的AT指令
  * @param  Send_Num 发送数据时，字符串长度
  * @retval 无
  */
void AT_Send(char* Command, Command_StateTypeDef State)
{
	uint8_t Cmd[200] = { 0 };
	Error_Time = 0;		//超时时间清空
	
	if (!strcmp(Command, AT_CONNECT_WIFI))		//发送指令 AT_CONNECT_WIFI
	{
		Error_Cmd = AT_WIFI_ERROR;
		sprintf((char *)Cmd, "%s\"%s\",\"%s\"\r\n", Command, WIFI_ACCOUNT, WIFI_PASSWORD);
		HAL_UART_Transmit(&huart1, Cmd, sizeof(Cmd), 0xff);
	}
	else if (!strcmp(Command, AT_CONNECT_SERVER))		//发送指令 AT_CONNECT_SERVER
	{
		Error_Cmd = AT_SERVER_ERROR;
		if (State == HOME_SERVER_STATE)		//与本地TCP服务器连接
		{
			sprintf((char *)Cmd, "%s\"TCP\",\"%s\",%s\r\n", Command, SERVER_IP, SERVER_PORT_NUM);
		}
		else if (State == REMOTE_SERVER_STATE)		//与远端TCP服务器连接
		{
			sprintf((char *)Cmd, "%s\"TCP\",\"%s\",%s\r\n", Command, SERVER_URL, SERVER_TCP);
		}
		HAL_UART_Transmit(&huart1, Cmd, sizeof(Cmd), 0xff);
	}
	else if (State == SEND_DATA_STATE)		//发送数据
	{
		Error_Cmd = AT_SEND_ERROR;
		sprintf((char *)Cmd, "%s", Command);
		HAL_UART_Transmit(&huart1, Cmd, sizeof(Cmd), 0xff);
		Error_Time = WAITING_TIME - 1000;		//等待1000(MS)
	}
	else if (State == AT_CIPSEND_STATE)		//发送指令 AT_CIPSEND
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
		if (ErrorSkip_Flag)		//初始化时发生错误后不执行后面的初始化程序
		{
			return;
		}
		
		if (Error_Time >= WAITING_TIME)		//超时时间设置为WAITING_TIME(MS)
		{
			//错误处理，暂时不使用(使用时要将上面的break删除)
			if (Error_Cmd == AT_WIFI_ERROR)
			{
				ErrorSkip_Flag = 1;
				return;
			}
			else if (Error_Cmd == AT_SERVER_ERROR)
			{
				ErrorSkip_Flag = 1;
				return;
			}
			else if (Error_Cmd == AT_TIME_ERROR)
			{
				ErrorSkip_Flag = 1;
				return;
			}
			else if (Error_Cmd == AT_SEND_ERROR)
			{
				ErrorSkip_Flag = 1;
				return;
			}
		}
	}
	
	Error_Cmd = NO_ERROR;		//清除错误状态
	OK_Flag = 0;						//清除接收OK标志位
}

/**
  * @brief  退出透传模式
  * @param  无
  * @retval 无
  */
void Exit_CIPMODE_1(void)
{
	vTaskDelay(pdMS_TO_TICKS(100));
	HAL_UART_Transmit(&huart1, (uint8_t*)"+++", 3, 0xff);
}

/**
  * @brief  ESP8266初始化函数
  * @param  无
  * @retval 无
  */
void ESP8266_Init(void)
{
	ESP8266_RST();																			//初始化
	AT_Send(AT_STA, NO_STATE);													//设置为STA模式
	AT_Send(AT_CONNECT_WIFI, NO_STATE);									//连接WIFI
	AT_Send(AT_CONNECT_SERVER, REMOTE_SERVER_STATE);		//连接服务器
	AT_Send(AT_CIPMODE_1, NO_STATE);										//打开透传模式
	ErrorSkip_Flag = 0;																	//恢复发送功能
	if (Error_Cmd != NO_ERROR)
	{
		Error_Dispose();
	}
}

/**
  * @brief  错误处理函数(未完成)
  * @param  无
  * @retval 无
  */
void Error_Dispose(void)
{
	
}

/**
  * @brief  ESP8266发送字符串函数
  * @param  String 发送的数据
  * @retval 无
  */
void ESP8266_SendString(char* String)
{
	AT_Send(AT_CIPSEND, AT_CIPSEND_STATE);
	AT_Send(String, SEND_DATA_STATE);
}

/**
  * @brief  ESP8266复位函数
  * @param  无
  * @retval 无
  */
void ESP8266_RST(void)
{
	HAL_GPIO_WritePin(GPIO_RST, GPIO_PIN_RST, GPIO_PIN_RESET);
	vTaskDelay(pdMS_TO_TICKS(500));
	HAL_GPIO_WritePin(GPIO_RST, GPIO_PIN_RST, GPIO_PIN_SET);
	vTaskDelay(pdMS_TO_TICKS(500));
}

/**
  * @brief  ESP8266获取时间函数
  * @param  无
  * @retval 无
  */
void ESP8266_GetTime(void)
{
	//填写对应的appkey=？&sign=？
	ESP8266_SendString("GET http://api.k780.com:88/?app=life.time&appkey=74037&sign=c9228380d8d43a8b696406c77902ca87&format=json&HTTP/1.1\r\n");		//填写对应的appkey=？&sign=？
	Exit_CIPMODE_1();
	
	String_Search(Time_Transition, Time_Receive, "\"datetime_1\":\"", strlen("\"datetime_1\":\""), 20);
	
	String_Copy(Time_YMD, Time_Transition, 11);
	String_Copy(Time_HMS, Time_Transition + 11, 8);
	Time_YMD[10] = '\0';		//防止OLED显示函数卡死
	Time_HMS[8] = '\0';
}

/**
  * @brief  计时函数
  * @param  无
  * @retval 无
  */
void Time_Keeping(void)
{
	if (Time_Count >= 1000)
	{
		Time_Count = 0;
		Time_HMS[7]++;
		Time_Scope(7, ':', 1);
		Time_Scope(6, '7', 2);
		Time_Scope(4, ':', 1);
	}
}

/**
  * @brief  时间范围控制函数
  * @param  Num Time_HMS的第Num位；例：Num = 7，Time_HMS[7]为秒的个位
  * @param  CarryBit 到哪个数进位
  * @retval 无
  */
void Time_Scope(uint8_t Num, uint8_t i, char CarryBit)
{
	if (Time_HMS[Num] == CarryBit)
	{
		Time_HMS[Num] = '0';
		Time_HMS[Num - i]++;
	}
}

/**
  * @brief  字符串复制函数
  * @param  Str1    字符串1
  * @param  Str2    字符串2
  * @param  Length  要复制的长度
  * @retval 无
  */
void String_Copy(char* Str1, char* Str2, uint16_t Length)
{
	for (uint8_t i = 0; i < Length; i++)
	{
		Str1[i] = Str2[i];
	}
}

/**
  * @brief  字符串搜寻函数，用于搜寻Str2内的Search_Str内容，并将后面的内容复制给Str1
  * @param  Str1 存储字符串
  * @param  Str2 被复制字符串
  * @param  SearchStr 要复制的内容前面的字符串
  * @param  SearchStr_Length SearchStr的长度
  * @param  Copy_Length 复制内容的长度
  * @retval 
  */
void String_Search(char* Str1, char* Str2, char* SearchStr, uint16_t SearchStr_Length, uint16_t Copy_Length)
{
	for (uint16_t i = 0; i < (TIME_RECEIVE_SIZE - SearchStr_Length); i++)
	{
		if (My_Strcmp(Str2 + i, SearchStr, SearchStr_Length) == 0)
		{
			String_Copy(Str1, Str2 + i + SearchStr_Length, Copy_Length);
		}
	}
	
	return;
}

/**
  * @brief  FreeRTOS延迟函数
  * @param  Delay 延迟的时间(ms)
  * @retval 无
  */
void Bsp_Delay(uint32_t Delay)
{
	uint32_t _base, _delay;
	_base = SystemCoreClock / 1000;
	_delay = _base * Delay;
	
	while (_delay--)
	{
		__nop();
	}
}

