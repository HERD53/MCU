/**
  ******************************************************************************
  * @file         TFT.c
  * @brief        
	*							 This file provides firmware functions to manage the following
	*							 + 
  ******************************************************************************
  * @attention		
	*
	*	The required HAL header files such as gpio.h are included in main.h
	* 
  ******************************************************************************
  */

/* Include -------------------------------------------------------------------*/
#include "main.h"

/* Define --------------------------------------------------------------------*/
#define RST GPIO_PIN_3
#define DC GPIO_PIN_4
#define SCL GPIO_PIN_5
#define SDA GPIO_PIN_7

/* Variables -----------------------------------------------------------------*/
uint8_t First;

/* Init ----------------------------------------------------------------------*/
void SPI_WriteData(uint8_t Data)
{
	unsigned char i = 0;
	for(i = 8; i > 0; i--)
	{
		if(Data & 0x80)
		{
			LCD_SDA_SET;
		}
    else
		{
			LCD_SDA_CLR;
		}
		LCD_SCL_CLR;
		LCD_SCL_SET;
		Data <<= 1;
	}
}

//��Һ����дһ��8λָ��
void LCD_WriteIndex(uint8_t Index)
{
   LCD_DC_CLR;
	 SPI_WriteData(Index);
}

//��Һ����дһ��8λ����
void LCD_WriteData(uint8_t Data)
{
   LCD_DC_SET;
   SPI_WriteData(Data);
}

//��Һ����дһ��16λ����
void LCD_WriteData_16Bit(uint16_t Data)
{
   LCD_DC_SET;
	 SPI_WriteData(Data>>8);
	 SPI_WriteData(Data);
}

void Lcd_Reset(void)
{
	LCD_RST_CLR;
	HAL_Delay(100);
	LCD_RST_SET;
	HAL_Delay(50);
}

void ST7735_SetRotation(uint8_t rotation)
{
    uint8_t madctl = 0;

    switch (rotation)
    {
        case 0:
            madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_RGB;
            break;
        case 1:
            madctl = ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
            break;
        case 2:
            madctl = ST7735_MADCTL_RGB;
            break;
        case 3:
            madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
            break;
    }

    LCD_WriteIndex(ST7735_MADCTL);
    LCD_WriteData(madctl);
}

void LCD_Init(void)
{
	Lcd_Reset(); 						//Reset before LCD Init.

	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	LCD_WriteIndex(0x11);		//Sleep exit 
	HAL_Delay(120);
	
	LCD_WriteIndex(0xB1);
	LCD_WriteData(0x00);		//0x05	 
	LCD_WriteData(0x08);		//0x3A	 
	LCD_WriteData(0x05);		//0x3A
	LCD_WriteIndex(0xB2);
	LCD_WriteData(0x05);
	LCD_WriteData(0x3A);
	LCD_WriteData(0x3A);
	LCD_WriteIndex(0xB3);
	LCD_WriteData(0x05);
	LCD_WriteData(0x3A);
	LCD_WriteData(0x3A);
	LCD_WriteData(0x05);
	LCD_WriteData(0x3A);
	LCD_WriteData(0x3A);
	//------------------------------------End ST7735S Frame Rate-----------------------------------------//
	LCD_WriteIndex(0xB4); 	//Dot inversion
	LCD_WriteData(0x03);
	//------------------------------------ST7735S Power Sequence-----------------------------------------//
	LCD_WriteIndex(0xC0);
	LCD_WriteData(0x62);
	LCD_WriteData(0x02);
	LCD_WriteData(0x04);
	LCD_WriteIndex(0xC1);
	LCD_WriteData(0xC0);
	LCD_WriteIndex(0xC2);
	LCD_WriteData(0x0D);
	LCD_WriteData(0x00);
	LCD_WriteIndex(0xC3);
	LCD_WriteData(0x8D);
	LCD_WriteData(0x6A);
	LCD_WriteIndex(0xC4);
	LCD_WriteData(0x8D);
	LCD_WriteData(0xEE);
	//---------------------------------End ST7735S Power Sequence-------------------------------------//
	LCD_WriteIndex(0xC5); 	//VCOM
	LCD_WriteData(0x08);		//0x12
	//------------------------------------ST7735S Gamma Sequence-----------------------------------------//
	LCD_WriteIndex(0xE0);
	LCD_WriteData(0x03);
	LCD_WriteData(0x1B);
	LCD_WriteData(0x12);
	LCD_WriteData(0x11);
	LCD_WriteData(0x3F);
	LCD_WriteData(0x3A);
	LCD_WriteData(0x32);
	LCD_WriteData(0x34);
	LCD_WriteData(0x2F);
	LCD_WriteData(0x2B);
	LCD_WriteData(0x30);
	LCD_WriteData(0x3A);
	LCD_WriteData(0x00);
	LCD_WriteData(0x01);
	LCD_WriteData(0x02);
	LCD_WriteData(0x05);
	LCD_WriteIndex(0xE1);
	LCD_WriteData(0x03);
	LCD_WriteData(0x1B);
	LCD_WriteData(0x12);
	LCD_WriteData(0x11);
	LCD_WriteData(0x32);
	LCD_WriteData(0x2F);
	LCD_WriteData(0x2A);
	LCD_WriteData(0x2F);
	LCD_WriteData(0x2E);
	LCD_WriteData(0x2C);
	LCD_WriteData(0x35);
	LCD_WriteData(0x3F);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x01);
	LCD_WriteData(0x05);
	//------------------------------------End ST7735S Gamma Sequence-----------------------------------------//

	LCD_WriteIndex(0x3A);			//65k mode
	LCD_WriteData(0x05);
	//Lcd_WriteIndex(0x36); 	//65k mode
	//Lcd_WriteData(0x40);
	ST7735_SetRotation(0);		//����ͼ����ת�Ƕ�
	LCD_WriteIndex(0x29);			//Display on
	LCD_WriteIndex(0x2C);
	LCD_WriteIndex(0x29);			//Display on	
}

/*************************************************
	��������LCD_Set_Region
	���ܣ�����lcd��ʾ�����ڴ�����д�������Զ�����
	��ڲ�����xy�����յ�
	����ֵ����
*************************************************/
void LCD_SetRegion(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end)
{		
	LCD_WriteIndex(0x2a);
	LCD_WriteData(0x00);
	LCD_WriteData(x_start);		//Lcd_WriteData(x_start+2);
	LCD_WriteData(0x00);
	LCD_WriteData(x_end + 2);

	LCD_WriteIndex(0x2b);
	LCD_WriteData(0x00);
	LCD_WriteData(y_start + 0);
	LCD_WriteData(0x00);
	LCD_WriteData(y_end + 1);
	
	LCD_WriteIndex(0x2c);

}

/*************************************************
	��������LCD_Set_XY
	���ܣ�����lcd��ʾ��ʼ��
	��ڲ�����xy����
	����ֵ����
*************************************************/
void LCD_SetXY(uint16_t x, uint16_t y)
{
  	LCD_SetRegion(x, y, x, y);
}
	
/*************************************************
	��������LCD_DrawPoint
	���ܣ���һ����
	��ڲ�������
	����ֵ����
*************************************************/
void Gui_DrawPoint(uint16_t x, uint16_t y, uint16_t Color)
{
	LCD_SetRegion(x, y, x + 1, y + 1);
	LCD_WriteData_16Bit(Color);
}

/*****************************************
	�������ܣ���TFTĳһ�����ɫ                          
	���ڲ�����color  ����ɫֵ                                 
******************************************/
unsigned int LCD_ReadPoint(uint16_t x, uint16_t y)
{
  unsigned int Data;
  LCD_SetXY(x, y);

  //LCD_ReadData();//���������ֽ�
  //Data=Lcd_ReadData();
  LCD_WriteData(Data);
	
  return Data;
}

/*************************************************
��������Lcd_Clear
���ܣ�ȫ����������
��ڲ����������ɫCOLOR
����ֵ����
*************************************************/
void LCD_Clear(uint16_t Color)               
{	
	unsigned int i,m;
	LCD_SetRegion(0, 0, X_MAX_PIXEL - 1, Y_MAX_PIXEL - 1);
	LCD_WriteIndex(0x2C);
	for(i = 0; i < X_MAX_PIXEL; i++)
	for(m = 0; m < Y_MAX_PIXEL; m++)
	{	
		LCD_WriteData_16Bit(Color);
	}   
}

/*************************************************
��������LCD_GBR2RGB
���ܣ�GBRתRGB����
��ڲ�����GBR��ɫ����
����ֵ��RGB��ɫ����
*************************************************/
uint16_t LCD_GBR2RGB(uint16_t c)
{
  uint16_t  r, g, b, rgb;   
  b = (c >> 0) & 0x1f;
  g = (c >> 5) & 0x3f;
  r = (c >> 11) & 0x1f;	 
  rgb = (b << 11) + (g << 5) + (r << 0);		
	
  return (rgb);
}

/**
  * @brief  ��Ļ�ϻ�Բ
  * @param  X Բ�ĵ�X����
  * @param  Y Բ�ĵ�Y����
  * @param  R Բ�İ뾶
  * @param  Color Բ����ɫ
  * @param  Thickness Բ����ɫ
  * @retval 
  */
void Gui_Circle(uint16_t X, uint16_t Y, uint16_t R, uint16_t Color, uint8_t Thickness)
{
	//Bresenham�㷨 
	unsigned short a, b;
	int c;
	a = 0;
	b = R;
	c = 3 - 2 * R;
	
	while (a < b)
	{
		Gui_DrawPoint(X + a, Y + b, Color);     //        7
		Gui_DrawPoint(X - a, Y + b, Color);     //        6
		Gui_DrawPoint(X + a, Y - b, Color);     //        2
		Gui_DrawPoint(X - a, Y - b, Color);     //        3
		Gui_DrawPoint(X + b, Y + a, Color);     //        8
		Gui_DrawPoint(X - b, Y + a, Color);     //        5
		Gui_DrawPoint(X + b, Y - a, Color);     //        1
		Gui_DrawPoint(X - b, Y - a, Color);     //        4
	
		if(c < 0) 
		{
			c = c + 4 * a + 6;
		}
		else
		{
			c = c + 4 * (a - b) + 10;
			b -= 1;
		}
		a += 1;
	}
	
	if (a == b) 
	{
			Gui_DrawPoint(X + a, Y + b, Color);
			Gui_DrawPoint(X + a, Y + b, Color);
			Gui_DrawPoint(X + a, Y - b, Color);
			Gui_DrawPoint(X - a, Y - b, Color);
			Gui_DrawPoint(X + b, Y + a, Color);
			Gui_DrawPoint(X - b, Y + a, Color);
			Gui_DrawPoint(X + b, Y - a, Color);
			Gui_DrawPoint(X - b, Y - a, Color);
	}
	
	if (!First)
	{
		First = 1;
		for (uint8_t i = 1; i < Thickness; i++)
		{
			Gui_Circle(X, Y, R + i, Color, 1);
			Gui_Circle(X, Y, R - i, Color, 1);
		}
	}
}