/**
  ******************************************************************************
  * @file         MPU6050.c
  * @brief        陀螺仪模块
	*							 This file provides firmware functions to manage the following
	*							 + 陀螺仪的数据解析；姿态检测；
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* 该文件包含I2C2，需要在STM32CubeMX中配置开启
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"

/* Define ----------------------------------------------------------------------*/
#define SMPLRT_DIV   0x19  // 采样率分频，典型值：0x07(125Hz) */
#define CONFIG       0x1A  // 低通滤波频率，典型值：0x06(5Hz) */
#define GYRO_CONFIG  0x1B  // 陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s) */
#define ACCEL_CONFIG 0x1C  // 加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz) */

#define ACCEL_XOUT_H 0x3B  // 存储最近的X轴、Y轴、Z轴加速度感应器的测量值 */
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

#define TEMP_OUT_H   0x41  // 存储的最近温度传感器的测量值 */
#define TEMP_OUT_L   0x42

#define GYRO_XOUT_H  0x43  // 存储最近的X轴、Y轴、Z轴陀螺仪感应器的测量值 */
#define GYRO_XOUT_L  0x44 
#define GYRO_YOUT_H  0x45
#define GYRO_YOUT_L  0x46
#define GYRO_ZOUT_H  0x47
#define GYRO_ZOUT_L  0x48

#define PWR_MGMT_1   0x6B   // 电源管理，典型值：0x00(正常启用) */
#define WHO_AM_I     0x75		// IIC地址寄存器(默认数值0x68，只读) */
#define MPU6050_ADDR 0xD0		// MPU6050手册上的地址，这里也可以使用serch函数去搜索
/* Variables --------------------------------------------------------------------*/
MPU6050_DataType MPU6050_Data;

/* I2C -----------------------------------------------------------------*/
int8_t Sensor_I2C2_Read(uint16_t DevAddr, uint16_t MemAddr, uint8_t *oData, uint8_t DataLen)
{
	return HAL_I2C_Mem_Read(&hi2c2, DevAddr, MemAddr, 1, oData, DataLen, 1000);
}

int8_t Sensor_I2C2_Write(uint16_t DevAddr, uint16_t MemAddr, uint8_t *iData, uint8_t DataLen)
{
	return HAL_I2C_Mem_Write(&hi2c2, DevAddr, MemAddr, 1, iData, DataLen, 1000);
}

/* Init -----------------------------------------------------------------*/
uint8_t MPU6050_Init(int16_t Addr)
{
	uint8_t check;
	
	HAL_I2C_Mem_Read(&hi2c2, Addr, WHO_AM_I, 1, &check, 1, 1000);
	
	if(check == 0x68)		//确认设备用 地址寄存器
	{	
		check = 0x00;
		Sensor_I2C2_Write(Addr, PWR_MGMT_1, &check, 1); 	    // 唤醒
		check = 0x07;	
		Sensor_I2C2_Write(Addr, SMPLRT_DIV, &check, 1);	    // 1Khz的速率
		check = 0x00;
		Sensor_I2C2_Write(Addr, ACCEL_CONFIG, &check, 1);	 	// 加速度配置
		check = 0x00;
		Sensor_I2C2_Write(Addr, GYRO_CONFIG, &check, 1);		// 陀螺配置
		return 0;
	}
	
	return -1;
}

static int16_t Mpu6050Addr = 0xD0;

int16_t Sensor_I2C2_Serch(void)
{
	for(uint8_t i = 1; i < 255; i++)
	{
		if(HAL_I2C_IsDeviceReady(&hi2c2, i, 1, 1000) == HAL_OK)
		{
			Mpu6050Addr = i;
			return i;
		}
	}
	return 0xD1;
}

void MPU6050_Read_Accel(void)
{
	uint8_t Read_Buf[6];
	
	// 寄存器依次是加速度X高 - 加速度X低 - 加速度Y高位 - 加速度Y低位 - 加速度Z高位 - 加速度度Z低位
	Sensor_I2C2_Read(Mpu6050Addr, ACCEL_XOUT_H, Read_Buf, 6); 
	
	MPU6050_Data.Accel_X = (int16_t)(Read_Buf[0] << 8 | Read_Buf[1]);
	MPU6050_Data.Accel_Y = (int16_t)(Read_Buf[2] << 8 | Read_Buf[3]);
	MPU6050_Data.Accel_Z = (int16_t)(Read_Buf[4] << 8 | Read_Buf[5]);
	
	MPU6050_Data.Accel_X = MPU6050_Data.Accel_X / 16384.0f;
	MPU6050_Data.Accel_Y = MPU6050_Data.Accel_Y / 16384.0f;
	MPU6050_Data.Accel_Z = MPU6050_Data.Accel_Z / 16384.0f;
	
}

void MPU6050_Read_Gyro(void)
{
	uint8_t Read_Buf[6];
	
	// 寄存器依次是角度X高 - 角度X低 - 角度Y高位 - 角度Y低位 - 角度Z高位 - 角度Z低位
	Sensor_I2C2_Read(Mpu6050Addr, GYRO_XOUT_H, Read_Buf, 6); 
	
	MPU6050_Data.Gyro_X = (int16_t)(Read_Buf[0] << 8 | Read_Buf[1]);
	MPU6050_Data.Gyro_Y = (int16_t)(Read_Buf[2] << 8 | Read_Buf[3]);
	MPU6050_Data.Gyro_Z = (int16_t)(Read_Buf[4] << 8 | Read_Buf[5]);
	
	MPU6050_Data.Gyro_X = MPU6050_Data.Gyro_X / 131.0f;
	MPU6050_Data.Gyro_Y = MPU6050_Data.Gyro_Y / 131.0f;
	MPU6050_Data.Gyro_Z = MPU6050_Data.Gyro_Z / 131.0f;
	
}

void MPU6050_Read_Temp(void)
{
  uint8_t Read_Buf[2];
	
	Sensor_I2C2_Read(Mpu6050Addr, TEMP_OUT_H, Read_Buf, 2); 
	
	MPU6050_Data.Temp = (int16_t)(Read_Buf[0] << 8 | Read_Buf[1]);
	
	MPU6050_Data.Temp = 36.53f + (MPU6050_Data.Temp / 340.0f);
}
