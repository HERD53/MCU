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
#include "semphr.h"

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
/* Definitions for Task_GetTime */
osThreadId_t Task_GetTimeHandle;
const osThreadAttr_t Task_GetTime_attributes = {
  .name = "Task_GetTime",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_OledShow */
osThreadId_t Task_OledShowHandle;
const osThreadAttr_t Task_OledShow_attributes = {
  .name = "Task_OledShow",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Mutex_OLED */
osMutexId_t Mutex_OLEDHandle;
const osMutexAttr_t Mutex_OLED_attributes = {
  .name = "Mutex_OLED"
};
/* Definitions for BinSem_OLED */
osSemaphoreId_t BinSem_OLEDHandle;
const osSemaphoreAttr_t BinSem_OLED_attributes = {
  .name = "BinSem_OLED"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void AppTask_GetTime(void *argument);
void AppTask_OledShow(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of Mutex_OLED */
  Mutex_OLEDHandle = osMutexNew(&Mutex_OLED_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of BinSem_OLED */
  BinSem_OLEDHandle = osSemaphoreNew(1, 0, &BinSem_OLED_attributes);

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
  /* creation of Task_GetTime */
  Task_GetTimeHandle = osThreadNew(AppTask_GetTime, NULL, &Task_GetTime_attributes);

  /* creation of Task_OledShow */
  Task_OledShowHandle = osThreadNew(AppTask_OledShow, NULL, &Task_OledShow_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_AppTask_GetTime */
/**
  * @brief  Function implementing the Task_GetTime thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_AppTask_GetTime */
void AppTask_GetTime(void *argument)
{
  /* USER CODE BEGIN AppTask_GetTime */
  /* Infinite loop */
	Boot_Num = 10;
	ESP8266_Init();
	ESP8266_GetTime();
	Boot_Num = 0;
	xSemaphoreGive(BinSem_OLEDHandle);
  for(;;)
  {
		Time_Keeping();
    vTaskDelay(pdMS_TO_TICKS(100));
  }
  /* USER CODE END AppTask_GetTime */
}

/* USER CODE BEGIN Header_AppTask_OledShow */
/**
* @brief Function implementing the Task_OledShow thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_OledShow */
void AppTask_OledShow(void *argument)
{
  /* USER CODE BEGIN AppTask_OledShow */
  /* Infinite loop */
  for(;;)
  {
		Boot_Animation();
		if (xSemaphoreTake(BinSem_OLEDHandle, portMAX_DELAY) == pdTRUE)
		{
			xSemaphoreGive(BinSem_OLEDHandle);
			OLED_Menu0();
		}
    vTaskDelay(pdMS_TO_TICKS(100));
  }
  /* USER CODE END AppTask_OledShow */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

