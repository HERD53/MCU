#include "gpio.h"

#define GPIOX GPIOB
#define GPIO_PIN_X GPIO_PIN_1

uint8_t Key_Read(void)
{
	if (HAL_GPIO_ReadPin(GPIOX, GPIO_PIN_X) == GPIO_PIN_RESET)
	{
		HAL_Delay(10);
		if (HAL_GPIO_ReadPin(GPIOX, GPIO_PIN_X) == GPIO_PIN_RESET)
		{
			return 1;
		}
	}
	return 0;
}
