#ifndef __ESP8266_H
#define __ESP8266_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
//User Macro
#define WIFI_ACCOUNT				"LZP2.4"								//WIFI名
#define WIFI_PASSWORD				"25608639"							//WIFI密码
#define SERVER_IP						"192.168.1.101"					//服务器IP地址
#define SERVER_PORT_NUM			"8080"									//服务器端口
#define SERVER_URL					"api.k780.com"					//服务器网址
#define SERVER_TCP					"80"										//TCP固定值

//Command Macro
#define AT_STA							"AT+CWMODE=1\r\n"				//STA模式
#define AT_CONNECT_WIFI			"AT+CWJAP_DEF="					//连接WIFI
#define AT_CONNECT_SERVER		"AT+CIPSTART="					//连接服务端
#define AT_CIPMODE_0				"AT+CIPMODE=0\r\n"			//普通模式
#define AT_CIPMODE_1				"AT+CIPMODE=1\r\n"			//透传模式
#define AT_CIPSEND					"AT+CIPSEND\r\n"				//发送

//Other Macro
#define TIME_RECEIVE_SIZE		30		//时间接收数组大小

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	NO_ERROR = 0u,
	AT_WIFI_ERROR,
	AT_SERVER_ERROR,
	AT_TIME_ERROR,
	AT_SEND_ERROR
} Command_ErrorTypeDef;

typedef enum
{
	NO_STATE = 0u,
	HOME_SERVER_STATE,
	REMOTE_SERVER_STATE,
	SEND_DATA_STATE,
	AT_CIPSEND_STATE
} Command_StateTypeDef;

extern volatile uint8_t OK_Flag;
extern Command_ErrorTypeDef Error_Cmd;
extern volatile uint32_t Error_Time;
extern char Time_Receive[TIME_RECEIVE_SIZE];
extern char Time_YMD[11];
extern char Time_HMS[9];

/* Initialization and de-initialization functions ----------------------------*/

/* Peripheral Control functions ----------------------------------------------*/
void Uart_Init(void);
void AT_Send(char* Command, Command_StateTypeDef State);
void Exit_CIPMODE_1(void);

void ESP8266_Init(void);
void ESP8266_SendString(char* String);
void ESP8266_RST(void);
void ESP8266_GetTime(void);

void String_Copy(char* Str1, char* Str2, uint16_t Length);

#endif
