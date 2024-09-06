/**
  ******************************************************************************
  * @file         MPU6050.c
  * @brief        ������ģ��
	*							 This file provides firmware functions to manage the following
	*							 + �����ǵ����ݽ�������̬��⣻
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* ���ļ�����I2C2����Ҫ��STM32CubeMX�����ÿ���
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"

/* Define ----------------------------------------------------------------------*/
#define SMPLRT_DIV   0x19  // �����ʷ�Ƶ������ֵ��0x07(125Hz) */
#define CONFIG       0x1A  // ��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz) */
#define GYRO_CONFIG  0x1B  // �������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s) */
#define ACCEL_CONFIG 0x1C  // ���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz) */

#define ACCEL_XOUT_H 0x3B  // �洢�����X�ᡢY�ᡢZ����ٶȸ�Ӧ���Ĳ���ֵ */
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

#define TEMP_OUT_H   0x41  // �洢������¶ȴ������Ĳ���ֵ */
#define TEMP_OUT_L   0x42

#define GYRO_XOUT_H  0x43  // �洢�����X�ᡢY�ᡢZ�������Ǹ�Ӧ���Ĳ���ֵ */
#define GYRO_XOUT_L  0x44 
#define GYRO_YOUT_H  0x45
#define GYRO_YOUT_L  0x46
#define GYRO_ZOUT_H  0x47
#define GYRO_ZOUT_L  0x48

#define PWR_MGMT_1   0x6B   // ��Դ��������ֵ��0x00(��������) */
#define WHO_AM_I     0x75		// IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��) */
#define MPU6050_ADDR 0xD0		// MPU6050�ֲ��ϵĵ�ַ������Ҳ����ʹ��serch����ȥ����
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
	
	if(check == 0x68)		//ȷ���豸�� ��ַ�Ĵ���
	{	
		check = 0x00;
		Sensor_I2C2_Write(Addr, PWR_MGMT_1, &check, 1); 	    // ����
		check = 0x07;	
		Sensor_I2C2_Write(Addr, SMPLRT_DIV, &check, 1);	    // 1Khz������
		check = 0x00;
		Sensor_I2C2_Write(Addr, ACCEL_CONFIG, &check, 1);	 	// ���ٶ�����
		check = 0x00;
		Sensor_I2C2_Write(Addr, GYRO_CONFIG, &check, 1);		// ��������
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
	
	// �Ĵ��������Ǽ��ٶ�X�� - ���ٶ�X�� - ���ٶ�Y��λ - ���ٶ�Y��λ - ���ٶ�Z��λ - ���ٶȶ�Z��λ
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
	
	// �Ĵ��������ǽǶ�X�� - �Ƕ�X�� - �Ƕ�Y��λ - �Ƕ�Y��λ - �Ƕ�Z��λ - �Ƕ�Z��λ
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
