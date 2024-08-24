#ifndef __Uart_H
#define __Uart_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"

/* Variables -----------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
void Uart_Init(void);
void Uart_Send(uint8_t Uart_Data);

#endif
