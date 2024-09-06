#ifndef __TFT_H
#define __TFT_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"

/* Variables -----------------------------------------------------------------*/
//SPI���ݴ��䶨��
#define LCD_SCL_SET		(HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET))
#define LCD_SCL_CLR		(HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET))

#define LCD_SDA_SET		(HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET))
#define LCD_SDA_CLR		(HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET))

#define LCD_DC_SET		(HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET))
#define LCD_DC_CLR		(HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET))

#define LCD_RST_SET		(HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET))
#define LCD_RST_CLR		(HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET))

//LCD�����
#define ST7735_MADCTL     0x36
#define ST7735_MADCTL_MX  0x40
#define ST7735_MADCTL_MY  0x80
#define ST7735_MADCTL_MV  0x20
#define ST7735_MADCTL_RGB 0x00

//LCD��Χ����
#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        165

//LCD��ɫ����
#define RED  		0xF800
#define GREEN		0x07E0
#define BLUE 		0x001F
#define WHITE		0xFFFF
#define BLACK		0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D		//��ɫ0 3165 00110 001011 00101
#define GRAY1   0x8410		//��ɫ1      00000 000000 00000
#define GRAY2   0x4208		//��ɫ2  1111111111011111

/* Function prototypes -------------------------------------------------------*/
//��������
void LCD_Init(void);
void LCD_SetRegion(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end);
void LCD_SetXY(uint16_t x, uint16_t y);
unsigned int LCD_ReadPoint(uint16_t x, uint16_t y);
//��ͼ����
void LCD_Clear(uint16_t Color);
uint16_t LCD_GBR2RGB(uint16_t Color);
void Gui_DrawPoint(uint16_t x, uint16_t y, uint16_t Color);
void Gui_Circle(uint16_t X, uint16_t Y, uint16_t R, uint16_t Color, uint8_t Size);

#endif
