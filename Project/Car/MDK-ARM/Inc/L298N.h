#ifndef __L298N_H
#define __L298N_H

void L298N_Init(void);
void L298N_Front(int16_t Speed);
void L298N_Rear(int16_t Speed);
void L298N_Left(int16_t Speed);
void L298N_Right(int16_t Speed);

#endif
