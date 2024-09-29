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
// 按键
#define GPIO_KEY					GPIOB					// 按键的GPIOX值
#define GPIO_PIN_KEY			GPIO_PIN_13		// 按键的GPIO_PIN_X值
// 摇杆
#define GPIO_ROCKER				GPIOA					// 摇杆按键的GPIOX值
#define GPIO_PIN_ROCKER		GPIO_PIN_2		// 摇杆按键的GPIO_PIN_X值

#define MENU0_NUM		(sizeof(Menu0) / sizeof(Menu0[0]))		// 菜单0的选项数
#define MENU1_NUM		(sizeof(Menu1) / sizeof(Menu1[0]))		// 菜单1的选项数
#define MENU2_NUM		(sizeof(Menu2) / sizeof(Menu2[0]))		// 菜单2的选项数

/* Variables ------------------------------------------------------------------*/
// 开机动画
volatile uint8_t BootNum;
// 菜单
MenuItem *CurrentMenu = Menu0;
volatile uint16_t MenuCursor = 1;
MenuItem Menu0[1] = 
{
	{"Start", Start_Menu, Menu1, NULL}
};
MenuItem Menu1[1] = 
{
	{"Option", Option_Menu, Menu2, Menu0}
};
MenuItem Menu2[4] = 
{
	{"Seting", Seting_Menu, NULL, Menu1},
	{"Error", Error_Menu, NULL, Menu1},
	{"White", White_Menu, NULL, Menu1},
	{"Black", Black_Menu, NULL, Menu1}
};
uint16_t SubmenusNum = MENU0_NUM;			// 子菜单数 (赋值为开始菜单的子菜单数)
uint16_t OptionsFlag = 0;							// 选项标志位 (赋值为开始菜单无选项)

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
	
	for (uint8_t i = 0; i < BootNum; i++)
	{
		OLED_Clear();
		sprintf(Animation, "Wait");
		OLED_Printf(10 * i, 23, 8, "%s", Animation);
		OLED_Update();
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

/**
  * @brief  按键/摇杆读取函数
  * @param  无
  * @retval 无
  */
void Peripheral_Read(void)
{
	GPIO_PinState KeyState;
	GPIO_PinState RockerKeyState;
	KeyState = HAL_GPIO_ReadPin(GPIO_KEY, GPIO_PIN_KEY);						// 读取到的按键状态给KeyState
	RockerKeyState = HAL_GPIO_ReadPin(GPIO_ROCKER, GPIO_PIN_ROCKER);		// 读取到的摇杆按键状态给RockerState
	
	if (KeyState == GPIO_PIN_RESET)
	{
		// 按键按下后执行任务
		if (CurrentMenu == Menu1)		// 返回上级菜单
		{
			CurrentMenu = Menu1->ParentMenu;		// 跳转到Menu0
			OptionsFlag = 0;              			// 无选项
			MenuCursor = 1;											// 光标在第一位
		}
		else if (CurrentMenu == Menu2 || CurrentMenu == &(Menu2[1]) || CurrentMenu == &(Menu2[2]) || CurrentMenu == &(Menu2[3]))
		{
			CurrentMenu = Menu2->ParentMenu;		// 跳转到Menu0
			OptionsFlag = 1;              			// 无选项
			MenuCursor = 1;											// 光标在第一位
			SubmenusNum = MENU2_NUM;						// 四个选项
		}
	}
	
	if (RockerKeyState == GPIO_PIN_RESET)
	{
		// 摇杆按下后执行任务
		if (CurrentMenu == Menu0)		// Menu0菜单下按下按键；MenuCursor不能等于0否则数组溢出；
		{
			CurrentMenu = Menu1;				// 跳转到Menu1
			OptionsFlag = 1;						// 有选项
			MenuCursor = 1;							// 光标在第一位
			SubmenusNum = MENU2_NUM;		// 四个选项
		}
		else if (CurrentMenu == Menu1)
		{
			CurrentMenu = &Menu2[MenuCursor - 1];		// 跳转到Menu1
			OptionsFlag = 1;												// 有选项
			MenuCursor = 1;													// 光标在第一位
			SubmenusNum = 2;												// 两个选项
		}
	}
	
	if (RockerUD == DOWN && OptionsFlag)
	{
		// 摇杆向上后执行任务
		if (++MenuCursor >= (SubmenusNum + 1))
		{
			MenuCursor = 1;
		}
		vTaskDelay(pdMS_TO_TICKS(200));
	}
	else if (RockerUD == UP && OptionsFlag)
	{
		// 摇杆向下后执行任务
		if (--MenuCursor <= 0)
		{
			MenuCursor = SubmenusNum;
		}
		vTaskDelay(pdMS_TO_TICKS(200));
	}
	
	vTaskDelay(pdMS_TO_TICKS(200));
}

/**
  * @brief  开始菜单
  * @param  无
  * @retval 无
  */
void Start_Menu(void)
{
	OLED_Clear();
	OLED_Printf(0, 0, 8, "%s", Time_HMS);
	OLED_Printf(0, 16, 8, "%s", Time_YMD);
}

void Option_Menu(void)
{
	OLED_Clear();
	OLED_Printf(0, 0, 8, "Seting");
	OLED_Printf(0, 16, 8, "Error");
	OLED_Printf(0, 32, 8, "White");
	OLED_Printf(0, 48, 8, "Black");
}

/**
  * @brief  设置菜单函数
  * @param  无
  * @retval 无
  */
void Seting_Menu(void)
{
	OLED_Clear();
	OLED_Printf(0, 0, 8, "1....");
	OLED_Printf(0, 16, 8, "2....");
}

/**
  * @brief  设置菜单函数
  * @param  无
  * @retval 无
  */
void Error_Menu(void)
{
	OLED_Clear();
	OLED_Printf(0, 0, 8, "Error");
}

/**
  * @brief  白色菜单函数
  * @param  无
  * @retval 无
  */
void White_Menu(void)
{
	OLED_Clear();
	OLED_Printf(0, 0, 8, "3....");
}

/**
  * @brief  黑色菜单函数
  * @param  无
  * @retval 无
  */
void Black_Menu(void)
{
	OLED_Clear();
	OLED_Printf(0, 0, 8, "4....");
}

/**
  * @brief  菜单反色函数
  * @param  Num 第Num行
  * @retval 无
  */
void OledMenu_Inverse(uint16_t Num)
{
	if (Num == 1)
	{
		OLED_UpdateArea_Inverse(0, 0, 127, 16);
		OLED_UpdateArea(0, 16, 127, 48);
	}
	else if (Num == 2)
	{
		OLED_UpdateArea_Inverse(0, 16, 127, 16);
		OLED_UpdateArea(0, 0, 127, 16);
		OLED_UpdateArea(0, 32, 127, 32);
	}
	else if (Num == 3)
	{
		OLED_UpdateArea_Inverse(0, 32, 127, 16);
		OLED_UpdateArea(0, 0, 127, 32);
		OLED_UpdateArea(0, 48, 127, 16);
	}
	else if (Num == 4)
	{
		OLED_UpdateArea_Inverse(0, 48, 127, 16);
		OLED_UpdateArea(0, 0, 127, 48);
	}
	else if (Num == 5)
	{
		OLED_UpdateArea(0, 0, 127, 64);
	}
}
