#ifndef __BootLoader_H
#define __BootLoader_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported constants --------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef void (*load_a_t)(void);

/* Exported macro ------------------------------------------------------------*/
#define STM32_FLASH_START_ADDRESS		0x08000000																														//FLASH起始地址
#define STM32_PAGE_SIZE							1024																																	//FLASH单个扇区的大小
#define STM32_PAGE_NUM							64																																		//FLASH总扇区个数
#define STM32_B_PAGE_NUM						20																																		//B区扇区个数
#define STM32_A_PAGE_NUM						(STM32_PAGE_NUM - STM32_B_PAGE_NUM)																		//A区扇区个数
#define STM32_A_START_ADDRESS				(STM32_FLASH_START_ADDRESS + (STM32_B_PAGE_NUM * STM32_PAGE_SIZE))		//A区起始地址

/* Initialization and de-initialization functions ----------------------------*/
void BootLoader_Init(void);

/* Peripheral Control functions ----------------------------------------------*/
__asm void MSR_SP(uint32_t Addr);
void LOAD_A(uint32_t Addr);

#endif
