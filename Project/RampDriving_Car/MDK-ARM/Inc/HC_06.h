#ifndef __HC_06_H
#define __HC_06_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"

/* Variables -----------------------------------------------------------------*/
extern uint8_t Speed;
extern uint8_t Car_State;
extern uint8_t Ctrl_State;

/* Function prototypes -------------------------------------------------------*/
void HC06_Init(void);
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);

#endif
