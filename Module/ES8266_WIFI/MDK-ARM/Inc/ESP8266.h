#ifndef __ESP8266_H
#define __ESP8266_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
//User Macro
#define WIFI_ACCOUNT				"LZP2.4"								//WIFI��
#define WIFI_PASSWORD				"25608639"							//WIFI����
#define SERVER_IP						"192.168.1.101"					//������IP��ַ
#define SERVER_PORT_NUM			"8080"									//�������˿�
#define SERVER_URL					"api.k780.com"					//��������ַ
#define SERVER_TCP					"80"										//TCP�̶�ֵ

//Command Macro
#define AT_STA							"AT+CWMODE=1\r\n"				//STAģʽ
#define AT_CONNECT_WIFI			"AT+CWJAP_DEF="					//����WIFI
#define AT_CONNECT_SERVER		"AT+CIPSTART="					//���ӷ����
#define AT_CIPMODE_0				"AT+CIPMODE=0\r\n"			//��ͨģʽ
#define AT_CIPMODE_1				"AT+CIPMODE=1\r\n"			//͸��ģʽ
#define AT_CIPSEND					"AT+CIPSEND\r\n"				//����

//Other Macro
#define TIME_RECEIVE_SIZE		30		//ʱ����������С

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
