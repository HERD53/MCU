/**
  ******************************************************************************
  * @file         Animation.c
  * @brief       	OLED��������
	*							 This file provides firmware functions to manage the following
	*							 + OLED��ʾ����
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
// ����
#define GPIO_KEY					GPIOB					// ������GPIOXֵ
#define GPIO_PIN_KEY			GPIO_PIN_13		// ������GPIO_PIN_Xֵ
// ҡ��
#define GPIO_ROCKER				GPIOA					// ҡ�˰�����GPIOXֵ
#define GPIO_PIN_ROCKER		GPIO_PIN_2		// ҡ�˰�����GPIO_PIN_Xֵ

#define MENU0_NUM		(sizeof(Menu0) / sizeof(Menu0[0]))		// �˵�0��ѡ����
#define MENU1_NUM		(sizeof(Menu1) / sizeof(Menu1[0]))		// �˵�1��ѡ����
#define MENU2_NUM		(sizeof(Menu2) / sizeof(Menu2[0]))		// �˵�2��ѡ����

/* Variables ------------------------------------------------------------------*/
// ��������
volatile uint8_t BootNum;
// �˵�
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
uint16_t SubmenusNum = MENU0_NUM;			// �Ӳ˵��� (��ֵΪ��ʼ�˵����Ӳ˵���)
uint16_t OptionsFlag = 0;							// ѡ���־λ (��ֵΪ��ʼ�˵���ѡ��)

/* Initialization and de-initialization functions -----------------------------*/

/* Peripheral Control functions -----------------------------------------------*/
/**
  * @brief  ��������
  * @param  ��
  * @retval ��
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
  * @brief  ����/ҡ�˶�ȡ����
  * @param  ��
  * @retval ��
  */
void Peripheral_Read(void)
{
	GPIO_PinState KeyState;
	GPIO_PinState RockerKeyState;
	KeyState = HAL_GPIO_ReadPin(GPIO_KEY, GPIO_PIN_KEY);						// ��ȡ���İ���״̬��KeyState
	RockerKeyState = HAL_GPIO_ReadPin(GPIO_ROCKER, GPIO_PIN_ROCKER);		// ��ȡ����ҡ�˰���״̬��RockerState
	
	if (KeyState == GPIO_PIN_RESET)
	{
		// �������º�ִ������
		if (CurrentMenu == Menu1)		// �����ϼ��˵�
		{
			CurrentMenu = Menu1->ParentMenu;		// ��ת��Menu0
			OptionsFlag = 0;              			// ��ѡ��
			MenuCursor = 1;											// ����ڵ�һλ
		}
		else if (CurrentMenu == Menu2 || CurrentMenu == &(Menu2[1]) || CurrentMenu == &(Menu2[2]) || CurrentMenu == &(Menu2[3]))
		{
			CurrentMenu = Menu2->ParentMenu;		// ��ת��Menu0
			OptionsFlag = 1;              			// ��ѡ��
			MenuCursor = 1;											// ����ڵ�һλ
			SubmenusNum = MENU2_NUM;						// �ĸ�ѡ��
		}
	}
	
	if (RockerKeyState == GPIO_PIN_RESET)
	{
		// ҡ�˰��º�ִ������
		if (CurrentMenu == Menu0)		// Menu0�˵��°��°�����MenuCursor���ܵ���0�������������
		{
			CurrentMenu = Menu1;				// ��ת��Menu1
			OptionsFlag = 1;						// ��ѡ��
			MenuCursor = 1;							// ����ڵ�һλ
			SubmenusNum = MENU2_NUM;		// �ĸ�ѡ��
		}
		else if (CurrentMenu == Menu1)
		{
			CurrentMenu = &Menu2[MenuCursor - 1];		// ��ת��Menu1
			OptionsFlag = 1;												// ��ѡ��
			MenuCursor = 1;													// ����ڵ�һλ
			SubmenusNum = 2;												// ����ѡ��
		}
	}
	
	if (RockerUD == DOWN && OptionsFlag)
	{
		// ҡ�����Ϻ�ִ������
		if (++MenuCursor >= (SubmenusNum + 1))
		{
			MenuCursor = 1;
		}
		vTaskDelay(pdMS_TO_TICKS(200));
	}
	else if (RockerUD == UP && OptionsFlag)
	{
		// ҡ�����º�ִ������
		if (--MenuCursor <= 0)
		{
			MenuCursor = SubmenusNum;
		}
		vTaskDelay(pdMS_TO_TICKS(200));
	}
	
	vTaskDelay(pdMS_TO_TICKS(200));
}

/**
  * @brief  ��ʼ�˵�
  * @param  ��
  * @retval ��
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
  * @brief  ���ò˵�����
  * @param  ��
  * @retval ��
  */
void Seting_Menu(void)
{
	OLED_Clear();
	OLED_Printf(0, 0, 8, "1....");
	OLED_Printf(0, 16, 8, "2....");
}

/**
  * @brief  ���ò˵�����
  * @param  ��
  * @retval ��
  */
void Error_Menu(void)
{
	OLED_Clear();
	OLED_Printf(0, 0, 8, "Error");
}

/**
  * @brief  ��ɫ�˵�����
  * @param  ��
  * @retval ��
  */
void White_Menu(void)
{
	OLED_Clear();
	OLED_Printf(0, 0, 8, "3....");
}

/**
  * @brief  ��ɫ�˵�����
  * @param  ��
  * @retval ��
  */
void Black_Menu(void)
{
	OLED_Clear();
	OLED_Printf(0, 0, 8, "4....");
}

/**
  * @brief  �˵���ɫ����
  * @param  Num ��Num��
  * @retval ��
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
