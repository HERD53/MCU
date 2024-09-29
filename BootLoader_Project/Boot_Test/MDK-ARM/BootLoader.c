/**
  ******************************************************************************
  * @file         BootLoader.c
  * @brief        BootLoader Routines
	*							 This file provides firmware functions to manage the following
	*							 + OTA Updata
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

/* Variables -------------------------------------------------------------------*/
load_a_t load_a;

/* Initialization functions ----------------------------------------------------*/

/**
  * @brief  SPָ����ת����
  * @param  ��ת��ַ
  * @retval ��
  */
__asm void MSR_SP(uint32_t Addr)
{
	MSR MSP, r0
	BX r14
}

/**
  * @brief  FLASH��ת����
  * @param  ��ת���ַ
  * @retval ��
  */
void LOAD_A(uint32_t Addr)
{
	if ((*(uint32_t *) Addr >= 0x20000000) && (*(uint32_t *) Addr <= 0x20004FFF))
	{
		MSR_SP (*(uint32_t *)Addr);
		load_a = (load_a_t)*(uint32_t *) (Addr + 4);
		load_a();
	}
}

/**
  * @brief  Boot��ʼ������
  * @param  ��
  * @retval ��
  */
void BootLoader_Init(void)
{
	
}
