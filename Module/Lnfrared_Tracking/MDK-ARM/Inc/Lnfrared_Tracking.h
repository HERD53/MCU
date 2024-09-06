#ifndef __Lnfrared_Tracking_H
#define __Lnfrared_Tracking_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Private define ------------------------------------------------------------*/
#define GPIOX GPIOA						//GPIOX (X...A,B,C)
#define LEFT_0 GPIO_PIN_0			//��ߵ�һ��������ģ��
#define LEFT_1 GPIO_PIN_1			//��ߵڶ���������ģ��
#define MIDDLE GPIO_PIN_2			//�м������ģ��
#define RIGHT_1 GPIO_PIN_3		//�ұߵڶ���������ģ��
#define RIGHT_0 GPIO_PIN_4		//�ұߵ�һ��������ģ��

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
uint8_t* Infrared_Judge(void);

#endif
