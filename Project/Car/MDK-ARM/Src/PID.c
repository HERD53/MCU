/**
  ******************************************************************************
  * @file         PID.c
  * @brief        PID调速 
	*							 This file provides firmware functions to manage the following
	*							 + 
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* 
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"

/* Define ----------------------------------------------------------------------*/

/* Variables --------------------------------------------------------------------*/
int8_t Error;								//误差
int8_t Last_Error;					//一次误差
int8_t Cumulative_Error;		//累积误差
int8_t Error_Difference;		//误差差值
float P;
float I;
float D;

/* Init -----------------------------------------------------------------*/

float PID(int8_t Expected_Data, int8_t Current_Data, float Kp, float Ki, float Kd)
{
	Error = Expected_Data - Current_Data;
	//P
	P = Kp * Error;
	//I
	Cumulative_Error += Error;
	I = Ki * Cumulative_Error;
	//D
	Error_Difference = Error - Last_Error;
	Last_Error = Error;
	D = Kd * Last_Error;
	
	return P + I + D;
}
