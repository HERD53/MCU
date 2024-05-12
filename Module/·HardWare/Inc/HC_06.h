#ifndef __HC_06_H
#define __HC_06_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"

/* Private define ------------------------------------------------------------*/
#define Receive_Num 64							//缓存数组大小

/* Private variables ---------------------------------------------------------*/
extern uint8_t Receive_Data[2];			//接收数组

/* Private function prototypes -----------------------------------------------*/
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);

#endif
