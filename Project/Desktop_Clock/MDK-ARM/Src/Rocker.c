/**
  ******************************************************************************
  * @file         Rocker.c
  * @brief       	ң�˿�������
	*							 This file provides firmware functions to manage the following
	*							 + ����ҡ����Ϣ
  ******************************************************************************
  * @attention		
	*	
	*	The required HAL header files such as gpio.h are included in main.h
	* 
  ******************************************************************************
  */

/* Include --------------------------------------------------------------------*/
#include "main.h"

/* Define ---------------------------------------------------------------------*/
#define ADC_VALSIZE		2

/* Variables ------------------------------------------------------------------*/
uint16_t ADC_Value[ADC_VALSIZE];
RockerDirectionTypeDef RockerUD;		// ����
RockerDirectionTypeDef RockerLR;		// ����

/* Initialization and de-initialization functions -----------------------------*/

/* Peripheral Control functions -----------------------------------------------*/
/**
  * @brief  ADC��ʼ������
  * @param  ��
  * @retval ��
  */
void RockerADC_Init(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC_Value, ADC_VALSIZE);
}

/**
  * @brief  ADCת������жϻص�����
  * @param  hadc ADC�ľ��
  * @retval ��
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if (hadc->Instance == ADC1)
	{
		if (ADC_Value[1] > 3000)
		{
			RockerUD = DOWN;
		}
		else if (ADC_Value[1] < 900)
		{
			RockerUD = UP;
		}
		else
		{
			RockerUD = MIDDLE;
		}
		
		if (ADC_Value[0] > 3000)
		{
			RockerLR = LEFT;
		}
		else if (ADC_Value[0] < 900)
		{
			RockerLR = RIGHT;
		}
		else
		{
			RockerLR = MIDDLE;
		}
	}
}

