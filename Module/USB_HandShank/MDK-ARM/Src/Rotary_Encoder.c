/**
  ******************************************************************************
  * @file         Rotary_Encoder.c
  * @brief        ��ת������ģ��
	*							 This file provides firmware functions to manage the following
	*							 + �����ת�����������ٶ��Լ����ٶ�
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* ���ļ�����TIM\���벶����Ҫ��STM32CubeMX�����ÿ���
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"

/* Init ----------------------------------------------------------------------*/
void Encoder_Init(void)
{
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);      //������������ʱ��
  __HAL_TIM_ENABLE_IT(&htim1,TIM_IT_UPDATE);
	__HAL_TIM_SET_COUNTER(&htim1, 10000);
//	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
//	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);
}

/* Define --------------------------------------------------------------------*/
#define GPIOX GPIOA
#define GPIO_PIN_A GPIO_PIN_8
#define GPIO_PIN_B GPIO_PIN_9
#define COUNTERNUM __HAL_TIM_GetCounter(&htim1)        //��ȡ��������ʱ���еļ���ֵ

/* Variables -----------------------------------------------------------------*/
int32_t Rotary_Encoder_Count;
int8_t Degree;

/**
  * @brief  ��ת���������
  * @param  ��
  * @retval ��ת�ĸ���
  */
uint32_t Encoder_Detection(void)
{
	if (Rotary_Encoder_Count % 2)
	{
		Rotary_Encoder_Count--;
	}
	
	if (Rotary_Encoder_Count >= 40)
	{
		return 0;
	}
	else if (Rotary_Encoder_Count <= -40)
	{
		return 0;
	}
	
	Degree = Rotary_Encoder_Count * 3;
}

/**
  * @brief  TIM ���벶���жϻص�����
  * @param  htim TIM�ľ��
  * @retval ��
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if ((htim == &htim1) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1))
	{
		if (HAL_GPIO_ReadPin(GPIOX, GPIO_PIN_B) == GPIO_PIN_RESET)
		{
			Rotary_Encoder_Count++;
		}
		else
		{
			Rotary_Encoder_Count--;
		}
	}
//	else if ((htim == &htim1) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2))
//	{
//		if (HAL_GPIO_ReadPin(GPIOX, GPIO_PIN_A) == GPIO_PIN_RESET)
//		{
//			Rotary_Encoder_Count++;
//		}
//		else
//		{
//			Rotary_Encoder_Count--;
//		}
//	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  //����Ǳ����������ж�,��10ms��,�����������˼�����Χ,��Ҫ���д���
	if (htim->Instance == htim1.Instance)
	{
		if(COUNTERNUM < 10000)	Rotary_Encoder_Count++;         //���ϼ�������10000�������+1
		else if(COUNTERNUM > 10000)	Rotary_Encoder_Count--;     //���¼���С��0�������+1
		__HAL_TIM_SetCounter(&htim1, 10000);            				//�����趨��ʼֵ			
	}
}