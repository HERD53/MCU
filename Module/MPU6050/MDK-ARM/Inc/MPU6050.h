#ifndef __MPU6050_H
#define __MPU6050_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Variables -----------------------------------------------------------------*/
typedef struct{
	// 角速度
	float Accel_X;
	float Accel_Y;
	float Accel_Z;
	// 角度
	float Gyro_X;
	float Gyro_Y;
	float Gyro_Z;
	// 温度
	float Temp;
} MPU6050_DataType;

extern MPU6050_DataType MPU6050_Data;
/* Function prototypes -------------------------------------------------------*/
uint8_t MPU6050_Init(int16_t Addr);
int8_t Sensor_I2C2_Read(uint16_t DevAddr, uint16_t MemAddr, uint8_t *oData, uint8_t DataLen);
int8_t Sensor_I2C2_Write(uint16_t DevAddr, uint16_t MemAddr, uint8_t *iData, uint8_t DataLen);
void MPU6050_Read_Accel(void);
void MPU6050_Read_Gyro(void);
void MPU6050_Read_Temp(void);

#endif
