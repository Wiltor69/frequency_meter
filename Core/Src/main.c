/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
#include "math.h"

#define SEG_A_1 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1)
#define SEG_A_0 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0)
#define SEG_B_1 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1)
#define SEG_B_0 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0)
#define SEG_C_1 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1)
#define SEG_C_0 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0)
#define SEG_D_1 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1)
#define SEG_D_0 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0)
#define SEG_E_1 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1)
#define SEG_E_0 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0)
#define SEG_F_1 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1)
#define SEG_F_0 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0)
#define SEG_G_1 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, 1)
#define SEG_G_0  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, 0)
#define SEG_DP_1 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 1)
#define SEG_DP_0 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0)

#define RAZN_1_ON  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1)
#define RAZN_1_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 0)
#define RAZN_2_ON  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1)
#define RAZN_2_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0)
#define RAZN_3_ON  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1)
#define RAZN_3_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0)
#define RAZN_4_ON  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1)
#define RAZN_4_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0)

#define MINUS SEG_A_0; SEG_B_0; SEG_C_0; SEG_D_0; SEG_E_0; SEG_F_0; SEG_G_1;

#define TIME_DEL 1000

int num = 0;
bool old_but = 1;
bool new_but = 1;

int R1_1000, R2_100, R3_10, R4_1;

void numbers(int x);
bool debounce (bool old);
void chislo(int num);
void chislo_f(float num);
volatile uint8_t count_tim_it;
float num_ber;
float freq;

void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim)
{
	if(htim -> Instance == TIM6)
	{

	if(++count_tim_it > 4) count_tim_it = 1;

		if (num_ber < 0) {
			num_ber *= -1;
			if (count_tim_it == 1) {
				RAZN_2_OFF;
				RAZN_3_OFF;
				RAZN_4_OFF;
				RAZN_1_ON;
				MINUS;
				SEG_DP_0;
			}
			if (count_tim_it == 2) {
				RAZN_2_ON;
				RAZN_3_OFF;
				RAZN_4_OFF;
				RAZN_1_OFF;
				numbers(R2_100);
				if (num_ber >= 0 && num_ber < 10)
					SEG_DP_1;
				else
					SEG_DP_0;
			}
			if (count_tim_it == 3) {
				RAZN_2_OFF;
				RAZN_3_ON;
				RAZN_4_OFF;
				RAZN_1_OFF;
				numbers(R3_10);
				if (num_ber >= 10 && num_ber < 100)
					SEG_DP_1;
				else
					SEG_DP_0;
			}
			if (count_tim_it == 4) {
				RAZN_2_OFF;
				RAZN_3_OFF;
				RAZN_4_ON;
				RAZN_1_OFF;
				numbers(R4_1);
				SEG_DP_0;
			}
		}
	else {

			if (count_tim_it == 1) {
				RAZN_2_OFF;
				RAZN_3_OFF;
				RAZN_4_OFF;
				RAZN_1_ON;
				numbers(R1_1000);
				if (num_ber >= 0 && num_ber < 10)
					SEG_DP_1;
				else
					SEG_DP_0;
			}
			if (count_tim_it == 2) {
				RAZN_2_ON;
				RAZN_3_OFF;
				RAZN_4_OFF;
				RAZN_1_OFF;
				numbers(R2_100);
				if (num_ber >= 10 && num_ber < 100)
					SEG_DP_1;
				else
					SEG_DP_0;
			}
			if (count_tim_it == 3) {
				RAZN_2_OFF;
				RAZN_3_ON;
				RAZN_4_OFF;
				RAZN_1_OFF;
				numbers(R3_10);
				if (num_ber >= 100 && num_ber < 1000)
					SEG_DP_1;
				else
					SEG_DP_0;
			}
			if (count_tim_it == 4) {
				RAZN_2_OFF;
				RAZN_3_OFF;
				RAZN_4_ON;
				RAZN_1_OFF;
				numbers(R4_1);
				SEG_DP_0;
			}
		}
	}
}

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
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

_Bool First_Capture = 0;
uint32_t Cap_1 = 0;
uint32_t Cap_2 = 0;
uint32_t Cap_Diff = 0;

void HAL_TIM_IC_CaptureCallback (TIM_HandleTypeDef * htim)
{
	if(htim -> Instance == TIM2)
	{
		if(htim -> Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			if(First_Capture == 0)
			{
				Cap_1 =  HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
				First_Capture = 1;
			}
			else
			{
				Cap_2 =  HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

				if(Cap_2 > Cap_1)
				{
					Cap_Diff = Cap_2 - Cap_1;
				}
				else
				{
					Cap_Diff = 4294967295 - Cap_1 + Cap_2;
				}

				freq = 64000000.0 / Cap_Diff;
				__HAL_TIM_SET_COUNTER(htim, 0);
				First_Capture = 0;
			}
		}
	}
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM6_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM6_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  numbers(num);
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  num_ber = freq;

	  chislo_f(freq);

	  HAL_Delay(500);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 9999;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 31;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|LD2_Pin|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 LD2_Pin PA6 PA7
                           PA8 PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|LD2_Pin|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB4 PB5 PB6
                           PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PC7 PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
bool debounce (bool old)
{
	bool new = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0);
	if (new != old){
		HAL_Delay(6);
		new = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0);
		return new;
	}
    return new;
}



void numbers(int x)
{
	switch(x){

	case 0: SEG_A_1; SEG_B_1; SEG_C_1; SEG_D_1; SEG_E_1; SEG_F_1; SEG_G_0; SEG_DP_1;
	break;
	case 1: SEG_A_0; SEG_B_1; SEG_C_1; SEG_D_0; SEG_E_0; SEG_F_0; SEG_G_0; SEG_DP_1;
	break;
	case 2: SEG_A_1; SEG_B_1; SEG_C_0; SEG_D_1; SEG_E_1; SEG_F_0; SEG_G_1; SEG_DP_1;
	break;
	case 3: SEG_A_1; SEG_B_1; SEG_C_1; SEG_D_1; SEG_E_0; SEG_F_0; SEG_G_1; SEG_DP_1;
	break;
	case 4: SEG_A_0; SEG_B_1; SEG_C_1; SEG_D_0; SEG_E_1; SEG_F_1; SEG_G_1; SEG_DP_1;
	break;
	case 5: SEG_A_1; SEG_B_0; SEG_C_1; SEG_D_1; SEG_E_0; SEG_F_1; SEG_G_1; SEG_DP_1;
	break;
	case 6: SEG_A_1; SEG_B_0; SEG_C_1; SEG_D_1; SEG_E_1; SEG_F_1; SEG_G_1; SEG_DP_1;
	break;
	case 7: SEG_A_1; SEG_B_1; SEG_C_1; SEG_D_0; SEG_E_0; SEG_F_0; SEG_G_0; SEG_DP_1;
	break;
	case 8: SEG_A_1; SEG_B_1; SEG_C_1; SEG_D_1; SEG_E_1; SEG_F_1; SEG_G_1; SEG_DP_1;
	break;
	case 9: SEG_A_1; SEG_B_1; SEG_C_1; SEG_D_1; SEG_E_0; SEG_F_1; SEG_G_1; SEG_DP_1;
	break;
	default: SEG_A_1; SEG_B_1; SEG_C_0; SEG_D_0; SEG_E_0; SEG_F_1; SEG_G_1; SEG_DP_1;

	}

}

void chislo_f(float num)
{
	float num_old = num;

	if(num < 0) num *= -1;

	if (num_old < 0) {
		if (num >= 100)
			num *= 1;
		else if (num >= 10 && num < 100)
			num *= 10;
		else if (num >= 0 && num < 10)
			num *= 100;

		int num_int;
		num_int = lrint(num);


		R2_100 = num_int / 100;
		R3_10 = (num_int % 100) / 10;
		R4_1 = num_int % 10;
	}
	else {
		if (num >= 1000)
			num *= 1;
		else if (num >= 100 && num < 1000)
			num *= 10;
		else if (num >= 10 && num < 100)
			num *= 100;
		else if (num >= 0 && num < 10)
			num *= 1000;

		int num_int;
		num_int = lrint(num);

		R1_1000 = num_int / 1000;
		R2_100 = (num_int % 1000) / 100;
		R3_10 = (num_int % 100) / 10;
		R4_1 = num_int % 10;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
