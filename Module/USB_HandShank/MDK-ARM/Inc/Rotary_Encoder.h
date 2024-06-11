#ifndef __Rotary_Encoder_H
#define __Rotary_Encoder_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"

/* Variables -----------------------------------------------------------------*/
extern int32_t Rotary_Encoder_Count;
extern int8_t Degree;

/* Function prototypes -------------------------------------------------------*/
void Encoder_Init(void);
uint32_t Encoder_Detection(void);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

#endif
