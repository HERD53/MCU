#ifndef __Lnfrared_Tracking_H
#define __Lnfrared_Tracking_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Private define ------------------------------------------------------------*/
#define GPIOX GPIOA						//GPIOX (X...A,B,C)
#define LEFT_0 GPIO_PIN_0			//左边第一个红外检测模块
#define LEFT_1 GPIO_PIN_1			//左边第二个红外检测模块
#define MIDDLE GPIO_PIN_2			//中间红外检测模块
#define RIGHT_1 GPIO_PIN_3		//右边第二个红外检测模块
#define RIGHT_0 GPIO_PIN_4		//右边第一个红外检测模块

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
uint8_t* Infrared_Judge(void);

#endif
