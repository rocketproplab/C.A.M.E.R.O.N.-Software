/**
 ******************************************************************************
 * File Name          : main.c
 * Description        : Main program body
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <init/gpio.h>
#include <init/i2c.h>
#include <init/spi.h>
#include <init/usart.h>
#include "main.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ptadc.h"


// Function Prototypes
void SystemClock_Config(void); // Auto Generated
void testADC();
void testSol1();
void testTC2();
HAL_StatusTypeDef uartPrint(uint8_t* msg);
HAL_StatusTypeDef uartPrintBinary8(uint8_t bit, bool printNewline);

int main(void) {
	HAL_Init();
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_SPI1_Init();
	PTADC_Init();
	//MX_I2C1_Init();
	//MX_SPI3_Init();

	uartPrint((uint8_t*) "Hello, world\r\n\r\n");
	while (1) {
		testADC();
		HAL_Delay(1000);
	}
}

void testSol1() {
	uartPrint((uint8_t*) "Solenoid On");
	HAL_GPIO_WritePin(SOL_OUT1_GPIO_Port, SOL_OUT1_Pin, GPIO_PIN_SET);
	HAL_Delay(2000);

	uartPrint((uint8_t*) "Solenoid Off\r\n");
	HAL_GPIO_WritePin(SOL_OUT1_GPIO_Port, SOL_OUT1_Pin, GPIO_PIN_RESET);
	HAL_Delay(2000);
}

/**
 * Tests the 2nd Thermocouple (no reason why we chose the 2nd one)
 */
void testTC2() {

	uint8_t rxBuf[4] = { 0 };

	HAL_GPIO_WritePin(TC_CS2_GPIO_Port, TC_CS2_Pin, GPIO_PIN_RESET);
	//requires 32 bit buffer
	//rxBuf[31] is sign bit, rxBuf[30:18] are TC temperature(signed value)
	//rxBuf[15:4] is reference voltage
	HAL_SPI_Receive(&hspi1, rxBuf, (uint16_t) 4, TIMEOUT);

	HAL_GPIO_WritePin(TC_CS2_GPIO_Port, TC_CS2_Pin, GPIO_PIN_SET);

	for (int i = 0; i < 4; i++) {
		uartPrintBinary8(rxBuf[i], false);
		uartPrint((uint8_t*) " ");
	}
	uartPrint((uint8_t*) "\r\n");

}

/**
 * Tests the SPI ADC by writing/reading to/from its registers
 *
 * SPI Procedure for ADC:
 * 1) Write 1 byte, which sets the communication register
 * 2) The next byte(s) are dependent on what was set (read, write, etc)
 *
 * See datasheet for more info:
 * http://www.analog.com/media/en/technical-documentation/data-sheets/AD7794_7795.pdf
 */
void testADC() {
	uint32_t temp = PTADC_GetRawTempFromChannel(PT_CHANNEL_1);
	for (int i = 0; i < 4; i++)
		uartPrintBinary8(((uint8_t*)&temp)[i], false);
	uartPrint((uint8_t*)"\r\n");
}

/**
 * Prints  a string to UART2 for debugging
 *
 * Preconditions:
 * 	- UART2 is initialized
 * 	- msg is some normal string I guess, idk
 */
HAL_StatusTypeDef uartPrint(uint8_t* msg) {

	HAL_StatusTypeDef status;
	status = HAL_UART_Transmit(&huart2, msg, strlen((char*) msg), TIMEOUT);

	return status;
}

/**
 * Prints an 8-bit number as a binary number, with or without newline
 *
 * Preconditions:
 * 	- UART2 is initialized
 *
 * 	@param printNewline if true, also adds a newline (and CR)
 */
HAL_StatusTypeDef uartPrintBinary8(uint8_t num, bool printNewline) {

	HAL_StatusTypeDef status = HAL_OK;
	uint8_t bit;

	for (int i = 0; i < 8; i++) {
		bit = (num >> 7) + '0'; // Convert the left-most bit into ASCII
		HAL_UART_Transmit(&huart2, &bit, 1, TIMEOUT);

		num = num << 1;
	}

	if (printNewline)
		HAL_UART_Transmit(&huart2, (uint8_t*) "\r\n", 2, TIMEOUT);

	return status;
}

/** System Clock Configuration
 *
 * Currently using INTERNAL Oscillator
 *
 */
void SystemClock_Config(void) {

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	/**Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE()
	;

	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = 16;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 50;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure the Systick interrupt time
	 */
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	/**Configure the Systick
	 */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void _Error_Handler(char * file, int line) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT

/**
 * @brief Reports the name of the source file and the source line number
 * where the assert_param error has occurred.
 * @param file: pointer to the source file name
 * @param line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line) {
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */

}

#endif
