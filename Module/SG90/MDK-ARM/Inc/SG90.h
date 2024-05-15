#ifndef __SG90_H
#define __SG90_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Variables -----------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
void SteeringEngine_Control(uint32_t TIM_CHANNEL, uint8_t Angle);

#endif
