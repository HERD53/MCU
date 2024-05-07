#include "gpio.h"

uint16_t Key_Read(void)
{
	if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)))
	{
		HAL_Delay(20);
		while (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)));
		HAL_Delay(20);
		
		return 1;
	}
	
	return 0;
}
