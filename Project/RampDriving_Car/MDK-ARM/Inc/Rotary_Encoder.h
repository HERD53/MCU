#ifndef __Rotary_Encoder_H
#define __Rotary_Encoder_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"

/* Variables -----------------------------------------------------------------*/
extern float L_Speed;
extern float R_Speed;
extern uint32_t Encoder_Count_L1;
extern uint32_t Encoder_Count_L2;
extern uint32_t Encoder_Count_R1;
extern uint32_t Encoder_Count_R2;

/* Function prototypes -------------------------------------------------------*/
void Encoder_Init(void);
uint32_t Encoder_Detection(void);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

#endif
