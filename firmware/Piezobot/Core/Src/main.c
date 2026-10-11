/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "opamp.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "lcd_init.h"
#include "wave.h"
#include "HC_12.h"
#include "comm.h"
#include "protocol.h"
#include "string.h"
#include "math.h"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
  MX_DMA_Init();
  MX_DAC1_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_DAC3_Init();
  MX_OPAMP1_Init();
  MX_TIM7_Init();
  MX_TIM6_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, toothsheet_runwave_left, WAVE_LENTH, DAC_ALIGN_12B_R);
	HAL_DAC_Start_DMA(&hdac3, DAC_CHANNEL_1, (uint32_t*)toothsheet_runwave_right, WAVE_LENTH, DAC_ALIGN_12B_R);

	HAL_TIM_Base_Start_IT(&htim7);

	HAL_TIM_Base_Start(&htim6);


	HAL_OPAMP_Start(&hopamp1);

	LCD_Init();
	LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
	

	Comm_Init();

	HAL_StatusTypeDef hc12_ret;

	hc12_ret = HC12_Set(HC12_CMD_OK, 0);

	const char *hc12_msg;

	hc12_msg = (hc12_ret == HAL_OK) ? "OK\r\n" : "FAIL\r\n";
	HAL_UART_Transmit(&huart1, (uint8_t *)hc12_msg, (uint16_t)strlen(hc12_msg), 100U);

	Protocol_Init();


	/* optional HC-12 settings: uncomment one line to write it into the module */
//	hc12_ret = HC12_Set(HC12_CMD_B,  HC12_BAUD_9600);   /* baud rate        */
//	hc12_ret = HC12_Set(HC12_CMD_C,  21);               /* channel          */
//	hc12_ret = HC12_Set(HC12_CMD_FU, HC12_FU3);         /* transparent mode */
//	hc12_ret = HC12_Set(HC12_CMD_P,  HC12_P8);          /* TX power         */
//	hc12_ret = HC12_Set(HC12_CMD_DEFAULT, 0);           /* factory reset    */

	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//		LCD_ShowIntNum(20,82,16,2,RED,WHITE,16);
//		LCD_ShowString(80,40,"LCD_H:",RED,WHITE,16,0);
//		LCD_ShowIntNum(128,40,LCD_H,3,RED,WHITE,16);
//		LCD_ShowString(30,40,"LCD_H:",RED,WHITE,16,0);
//		LCD_ShowString(0,70,"Increaseing Nun:",RED,WHITE,16,0);
//		LCD_ShowFloatNum1(128,70,t,4,RED,WHITE,16);  
	while (1)
  {	
		if(receive_state == DONE)
		{
			
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);

			float spd   = received_data[LOCAL_ID - 1].speed;
			float angle = received_data[LOCAL_ID - 1].angle;
			float rate_left;
			float rate_right;

			if(angle > 0.0f)	/* steer left: slow the inner wheel */
			{
				rate_left  = spd * cosf(angle);	/* inner wheel scaled by cos(angle) */
				rate_right = spd;
			}
			else	/* steer right: slow the inner wheel */
			{
				rate_left  = spd;
				rate_right = spd * cosf(angle);	/* inner wheel scaled by cos(angle) */
			}

			RunWave_Gen(toothsheet_fullwave, rate_left,  toothsheet_runwave_left);
			RunWave_Gen(toothsheet_fullwave, rate_right, toothsheet_runwave_right);
			LCD_ShowFloatNum1(25, 82, rate_left,  4, RED, WHITE, 16);   /* rate left  */
			LCD_ShowFloatNum1(25, 98, rate_right, 4, RED, WHITE, 16);   /* rate right */
			receive_state = IDLE;
		}
		

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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
