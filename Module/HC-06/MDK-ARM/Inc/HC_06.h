#ifndef __HC_06_H
#define __HC_06_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"

/* Private define ------------------------------------------------------------*/
#define Receive_Num 64							//���������С

/* Private variables ---------------------------------------------------------*/
extern uint8_t Receive_Data[2];			//��������

/* Private function prototypes -----------------------------------------------*/
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);

#endif
