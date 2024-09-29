#ifndef __Animation_H
#define __Animation_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct MenuItem
{
	char *Name;											// 菜单名
	void (*Action)(void);						// 菜单函数
	struct MenuItem *SubMenu;				// 子菜单
	struct MenuItem *ParentMenu;		// 父菜单
} MenuItem;

extern volatile uint8_t BootNum;

extern MenuItem *CurrentMenu;
extern volatile uint16_t MenuCursor;
extern MenuItem Menu0[1];
extern MenuItem Menu1[1];
extern MenuItem Menu2[4];
extern uint16_t OptionsFlag;

/* Initialization and de-initialization functions ----------------------------*/

/* Peripheral Control functions ----------------------------------------------*/
void Boot_Animation(void);
void Peripheral_Read(void);
void Start_Menu(void);
void Option_Menu(void);
void Seting_Menu(void);
void Error_Menu(void);
void White_Menu(void);
void Black_Menu(void);
void OledMenu_Inverse(uint16_t Num);


#endif
