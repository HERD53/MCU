#ifndef __Animation_H
#define __Animation_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
extern volatile uint8_t Boot_Num;

/* Initialization and de-initialization functions ----------------------------*/

/* Peripheral Control functions ----------------------------------------------*/
void Boot_Animation(void);
void OLED_Menu0(void);

#endif
