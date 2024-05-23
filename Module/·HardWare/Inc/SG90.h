#ifndef __SG90_H
#define __SG90_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Variables -----------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
void SG90_Init(void);
void SteeringEngine_Control(uint8_t Angle);

#endif
