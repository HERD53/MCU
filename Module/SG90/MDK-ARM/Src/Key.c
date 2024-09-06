/**
  ******************************************************************************
  * @file         Key.c
  * @brief        ����ģ��
	*							 This file provides firmware functions to manage the following
	*							 + ��ⰴ���Ƿ���
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	*	���ļ�����GPIO��EXTI��TIM����Ҫ��STM32CubeMX�����ÿ���
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"
#include "Key.h"

/* Init ----------------------------------------------------------------------*/
//HAL_TIM_Base_Start_IT(&htim2);

/* Define --------------------------------------------------------------------*/
#define GPIOX GPIOB							//GPIOX (X...A,B,C)
#define GPIO_PIN_X GPIO_PIN_12		//GPIO_PIN_X (X...0,1,2,3,4,5,6,7)

/* Variables -----------------------------------------------------------------*/
uint32_t Key_Count;			//��ⳤ������
uint8_t Key_Tim_Flag;		//����������־λ
uint8_t Key_Flag;				//����������־λ

/**
  * @brief  EXTI�жϻص�����
  * @param  GPIO_Pin GPIO������
  * @retval ��
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_X)		//��ֹ����GPIO���Ŵ���
	{
		uint32_t num = 200000;
		while (num--);
		if (HAL_GPIO_ReadPin(GPIOX, GPIO_PIN_X) == GPIO_PIN_SET)		//��ֹ����
		{
			Key_Tim_Flag = 1;
			/* �û����뿪ʼ */
			
			/* �û�������� */
		}
		else
		{
			Key_Tim_Flag = 0;
			/* �û����뿪ʼ */
			
			/* �û�������� */
		}
	}
}

/**
  * @brief  TIM�жϻص�����
  * @param  htim TIM�ľ��
  * @retval ��
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim2)		//��ֹ������ʱ������
	{
		if (Key_Tim_Flag)
		{
			/* �������� */
			Key_Count++;
			if (Key_Count == 1000)		//��ʱ���ж�1ms����ʱ��Ϊ��ʱ1000ms
			{
				/* �������� */
				Key_Count = 0;		//�������
				Key_Flag = 1;			//�����������Լ������������ﵽ����������������
				/* �û����뿪ʼ */
				
				/* �û�������� */
			}
		}
		else
		{
			/* �����ɿ� */
			Key_Count = 0;		//��ֹ�ɿ����ٴγ�����ʱ�䲻���趨ֵ
			/* �û����뿪ʼ */
			
			/* �û�������� */
		}
	}
}

/**
  * @brief  �������ģ��
  * @param  ��
  * @retval ��
  */
void Key_Detection(void)
{
	if (HAL_GPIO_ReadPin(GPIOX, GPIO_PIN_X) == GPIO_PIN_SET)
	{
		/* ���°��� */
		Key_Tim_Flag = 1;
		HAL_Delay(20);
		if (HAL_GPIO_ReadPin(GPIOX, GPIO_PIN_X) == GPIO_PIN_SET)		//��ֹ����
		{
			/* �û����뿪ʼ */
			
			/* �û�������� */
		}
	}
	else
	{
		/* �ɿ����� */
		Key_Tim_Flag = 0;
		/* �û����뿪ʼ */
		
		/* �û�������� */
	}
}
