/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for Task_BootAnimat */
osThreadId_t Task_BootAnimatHandle;
const osThreadAttr_t Task_BootAnimat_attributes = {
  .name = "Task_BootAnimat",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_ESP8266 */
osThreadId_t Task_ESP8266Handle;
const osThreadAttr_t Task_ESP8266_attributes = {
  .name = "Task_ESP8266",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task_OledMenu */
osThreadId_t Task_OledMenuHandle;
const osThreadAttr_t Task_OledMenu_attributes = {
  .name = "Task_OledMenu",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for BinSem_OledMenu */
osSemaphoreId_t BinSem_OledMenuHandle;
const osSemaphoreAttr_t BinSem_OledMenu_attributes = {
  .name = "BinSem_OledMenu"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void AppTask_BootAnimation(void *argument);
void AppTask_ESP8266(void *argument);
void AppTask_OledMenu(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of BinSem_OledMenu */
  BinSem_OledMenuHandle = osSemaphoreNew(1, 0, &BinSem_OledMenu_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_BootAnimat */
  Task_BootAnimatHandle = osThreadNew(AppTask_BootAnimation, NULL, &Task_BootAnimat_attributes);

  /* creation of Task_ESP8266 */
  Task_ESP8266Handle = osThreadNew(AppTask_ESP8266, NULL, &Task_ESP8266_attributes);

  /* creation of Task_OledMenu */
  Task_OledMenuHandle = osThreadNew(AppTask_OledMenu, NULL, &Task_OledMenu_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_AppTask_BootAnimation */
/**
  * @brief  Function implementing the Task_BootAnimat thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_AppTask_BootAnimation */
void AppTask_BootAnimation(void *argument)
{
  /* USER CODE BEGIN AppTask_BootAnimation */
	
  /* Infinite loop */
	
  for(;;)
  {
		Boot_Animation();			// 开机动画
		Peripheral_Read();		// 按键/摇杆检测
		
		if (!BootNum)
		{
			ESP8266_GetTime();
			Time_Count = 0;
			vTaskDelay(pdMS_TO_TICKS(30000));
		}
		vTaskDelay(pdMS_TO_TICKS(1));
  }

  /* USER CODE END AppTask_BootAnimation */
}

/* USER CODE BEGIN Header_AppTask_ESP8266 */
/**
* @brief Function implementing the Task_ESP8266 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_ESP8266 */
void AppTask_ESP8266(void *argument)
{
  /* USER CODE BEGIN AppTask_ESP8266 */
	BootNum = 10;					// 开始开机动画
	ESP8266_Init();				// ESP8266初始化
	ESP8266_GetTime();		// 获取时间
	BootNum = 0;					// 关闭开机动画
	xSemaphoreGive(BinSem_OledMenuHandle);		// 释放信号量
	
  /* Infinite loop */
  for(;;)
  {
		Time_Keeping();		// 计时
    vTaskDelay(pdMS_TO_TICKS(1));
  }
  /* USER CODE END AppTask_ESP8266 */
}

/* USER CODE BEGIN Header_AppTask_OledMenu */
/**
* @brief Function implementing the Task_OledMenu thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_OledMenu */
void AppTask_OledMenu(void *argument)
{
  /* USER CODE BEGIN AppTask_OledMenu */
	xSemaphoreTake(BinSem_OledMenuHandle, portMAX_DELAY);		// 无限等待信号量
	
	/* Infinite loop */
  for(;;)
  {
		(CurrentMenu->Action)();		// 菜单运行
		if (OptionsFlag)						//判断是否反色显示
		{
			OledMenu_Inverse(MenuCursor);
		}
		else
		{
			OLED_Update();
		}
    vTaskDelay(pdMS_TO_TICKS(200));
  }
  /* USER CODE END AppTask_OledMenu */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

