/**
  ******************************************************************************
  * @file         Animation.c
  * @brief       	OLED动画驱动
	*							 This file provides firmware functions to manage the following
	*							 + OLED显示动画
  ******************************************************************************
  * @attention		
	*	
	*	The required HAL header files such as gpio.h are included in main.h
	* 
  ******************************************************************************
  */

/* Include --------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"

/* Define ---------------------------------------------------------------------*/

/* Variables ------------------------------------------------------------------*/
volatile uint8_t Boot_Num;

/* Initialization and de-initialization functions -----------------------------*/

/* Peripheral Control functions -----------------------------------------------*/
/**
  * @brief  开机动画
  * @param  无
  * @retval 无
  */
void Boot_Animation(void)
{
	char Animation[5] = { 0 };
	
	for (uint8_t i = 0; i < Boot_Num; i++)
	{
		OLED_Clear();
		sprintf(Animation, "Wait");
		OLED_Printf(10 * i, 23, 8, "%s", Animation);
		OLED_Update();
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

/**
  * @brief  一级菜单
  * @param  无
  * @retval 无
  */
void OLED_Menu0(void)
{
	uint8_t Cursor = 0;
	uint8_t Key_State_Flag = 0;
	
	OLED_Clear();
	OLED_Printf(0, 0, 8, "Time");
	OLED_Printf(0, 16, 8, "Seting");
	OLED_UpdateArea_Inverse(0, 0, 127, 16);
	OLED_UpdateArea(0, 16, 127, 16);
	
	while (1)
	{
		GPIO_PinState Key_State = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);					//按键
		GPIO_PinState RockerKey_State = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);		//摇杆按键
		
		if (Key_State == GPIO_PIN_RESET && !Key_State_Flag)
		{
			vTaskDelay(pdMS_TO_TICKS(200));
			if (++Cursor == 2)
			{
				Cursor = 0;
			}
			
			if (Cursor == 0)
			{
				OLED_UpdateArea_Inverse(0, 0, 127, 16);
				OLED_UpdateArea(0, 16, 127, 16);
			}
			else
			{
				OLED_UpdateArea_Inverse(0, 16, 127, 16);
				OLED_UpdateArea(0, 0, 127, 16);
			}
		}
		
		if (RockerKey_State == GPIO_PIN_RESET)
		{
			vTaskDelay(pdMS_TO_TICKS(200));
			if (Cursor == 0)
			{
				OLED_Clear();
				OLED_ShowString(0, 0, Time_HMS, 8);
				OLED_ShowString(0, 16, Time_YMD, 8);
				OLED_Update();
			}
			else
			{
				OLED_Clear();
				
				OLED_Update();
			}
			Key_State_Flag = 1;
		}
		
		vTaskDelay(pdMS_TO_TICKS(100));
	}
	
}


