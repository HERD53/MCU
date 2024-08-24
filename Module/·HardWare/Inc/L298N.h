#ifndef __L298N_H
#define __L298N_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Variables -----------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
void Car_Init(void);
void Car_Forward(uint8_t Speed);
void Car_Backwards(uint8_t Speed);
void Car_Left(uint8_t Speed);
void Car_Light(uint8_t Speed);

#endif
