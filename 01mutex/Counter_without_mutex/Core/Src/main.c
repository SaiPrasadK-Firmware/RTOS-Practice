#include "main.h"
#include "cmsis_os.h"
#include<stdint.h>
#include<string.h>
#include<stdio.h>
UART_HandleTypeDef huart2;
uint32_t counter = 0;

/* Task handles */
osThreadId_t IncrementTask1Handle;
const osThreadAttr_t Increment1Task_attributes = {
  .name = "IncrementTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t IncrementTask2Handle;
const osThreadAttr_t IncrementTask2_attributes = {
  .name = "IncrementTask2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Function prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void IncTask(void *argument);
void UART_Send_String(char *s);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  osKernelInitialize();
  UART_Send_String("Race Condition without mutex !\n");

  /* Create tasks */
  IncrementTask1Handle = osThreadNew(IncTask, "TASK 1", &Increment1Task_attributes);
  IncrementTask2Handle = osThreadNew(IncTask,"TASK 2", &IncrementTask2_attributes);

  osKernelStart();

  while (1) {}
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                              | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
    Error_Handler();
  }
}

static void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK) {
    Error_Handler();
  }
}



static void MX_GPIO_Init(void)
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
}

void IncTask(void *argument)
{
  char msg[50];
  char *taskName = (char *)argument;

  while (1)
  {
    if (counter < 100)   // total counts across both tasks
    {
      sprintf(msg, "%s: %u\r\n", taskName, (unsigned int)counter);
      counter++;
      UART_Send_String(msg);
    }
    else
    {


      osThreadSuspend(NULL);  // self-terminate
    }

    osDelay(1);
  }
}



/* UART send function */
void UART_Send_String(char *str)
{
  HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
}

void Error_Handler(void)
{
  __disable_irq();
  while (1) {}
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
  /* Optionally implement reporting of file/line */
}
#endif
