#ifndef __Rocker_H
#define __Rocker_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum {
	MIDDLE = 0u,
	UP,
	DOWN,
	LEFT,
	RIGHT
} RockerDirectionTypeDef;

extern uint16_t ADC_Value[2];
extern RockerDirectionTypeDef RockerUD;
extern RockerDirectionTypeDef RockerLR;

/* Initialization and de-initialization functions ----------------------------*/

/* Peripheral Control functions ----------------------------------------------*/
void RockerADC_Init(void);

#endif
