#ifndef __Uart_H
#define __Uart_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define CACHE_SIZE		256		//缓存数组大小

/* Exported types ------------------------------------------------------------*/
extern uint8_t Receive_Flag;
extern uint8_t Cache_Data[CACHE_SIZE];
extern uint32_t Cache_Count;

/* Initialization and de-initialization functions ----------------------------*/
void Uart_Init(void);

/* Peripheral Control functions ----------------------------------------------*/
uint8_t My_Strcmp(const char* Str1, const char* Str2, uint8_t Length);

#endif
