/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
//#include "cmsis_os.h"

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
TaskHandle_t Task1Handle;
TaskHandle_t Task2Handle;
/* USER CODE END Variables */
/* Definitions for defaultTask */
/* osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
}; */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void TaskPB13(void *argument);
void TaskPB14(void *argument);
void Delay(uint32_t gap);
extern void Error_Handler(void);
/* USER CODE END FunctionPrototypes */

// void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

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
  /* creation of defaultTask */
 // defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
      // Create Task for PB13
	BaseType_t status;

	status = xTaskCreate(TaskPB13,
                  "PB13Task",
                  128,        // stack size in words
                  NULL,
                  1,
                  &Task1Handle);

	if (status != pdPASS) Error_Handler();

      // Create Task for PB14
      status = xTaskCreate(TaskPB14,
                  "PB14Task",
                  128,
                  NULL,
                  3,
                  &Task2Handle);

      if (status != pdPASS) Error_Handler();
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
/*void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
 /* for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
// }

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void TaskPB13(void *argument)
  {
     for (;;)
      {
          // toggle PB13 high
          HAL_GPIO_TogglePin(GPIOB, task_1_Pin);
          // 5 ms delay
          vTaskDelay(pdMS_TO_TICKS(5));
      }
  }

  void TaskPB14(void *argument)
  {
     for (;;)
      {
          /* Block until notified by EXTI ISR */
                  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

                  HAL_GPIO_WritePin(GPIOB, task_2_Pin, GPIO_PIN_SET);
                  Delay(100000);

                  HAL_GPIO_WritePin(GPIOB, task_2_Pin, GPIO_PIN_RESET);
                  
      }
  }

  void Delay(uint32_t gap) {
      volatile uint32_t i;
      for(i = 0; i < gap; i++);
  }
/* USER CODE END Application */

