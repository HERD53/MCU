#ifndef __TB6612_H
#define __TB6612_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"

/* Variables -----------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
void Car_Init(void);
void Car_Stop(void);
void Car_Forward(uint8_t Speed);
void Car_Backwards(uint8_t Speed);
void Car_Left(uint8_t Speed);
void Car_Right(uint8_t Speed);

#endif
