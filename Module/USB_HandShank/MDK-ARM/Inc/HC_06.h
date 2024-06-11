#ifndef __HC_06_H
#define __HC_06_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"

/* Variables -----------------------------------------------------------------*/
extern int8_t x;
extern int8_t y;
extern int8_t key;

/* Function prototypes -------------------------------------------------------*/
void HC06_Init(void);
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);

#endif
