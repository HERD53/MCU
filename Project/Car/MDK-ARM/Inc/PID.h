#ifndef __PID_H
#define __PID_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Variables -----------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
float PID(int8_t Expected_Data, int8_t Current_Data, float Kp, float Ki, float Kd);

#endif
