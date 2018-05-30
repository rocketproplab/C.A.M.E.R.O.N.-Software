/*
 * 	File: ptadc.c
 *
 * 	Helper functions for the AD7794 ADC on CAMERON
 *
 * 	Author: George Troulis
 *
 * 	Ported from juliano77's Arduino library:
 * 	https://github.com/jjuliano77/JJ_AD7794
 */

#include "init/spi.h"
#include "init/gpio.h"
#include "init/usart.h"
#include "main.h"
#include "ptadc.h"

const uint8_t READ_DATA_REG = 0x58;
const uint8_t WRITE_CONF_REG = 0x10;
const uint8_t WRITE_MODE_REG = 0x08;

void PTADC_Init() {
	modeReg = 0x2001;	// Single Conversion mode, Fadc = 470Hz
	PTADC_ResetPT();
}

void PTADC_ResetPT() {

	uint32_t ADC_DATA_RESET = (uint32_t) (~0);
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, (uint8_t*) &ADC_DATA_RESET, 4, TIMEOUT);
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);
}

uint32_t PTADC_GetRawTempFromChannel(uint8_t channel) {
	// Set the current ADC Channel
	PTADC_SetActiveChannel(channel);

	// Starts the conversion procedure by writing to the mode register, then reading the result
	PTADC_StartConversion(&modeReg);
	uint32_t convResult = PTADC_GetConversionResult();

	return convResult;
}

void PTADC_SetActiveChannel(uint8_t channel) {
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	// Gain = 16x (input range: 156.2 mV from datasheet)
	uint8_t gain = 0b100;
	uint16_t confReg = (gain << 8) | channel;
	uint8_t conf_value[2];
	PTADC_WriteConfReg(&confReg);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);
}

void PTADC_WriteConfReg(uint16_t* confReg) {
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &WRITE_CONF_REG, 1, TIMEOUT);
	HAL_SPI_Transmit(&hspi1, (uint8_t*) confReg, 2, TIMEOUT);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);
}

void PTADC_StartConversion(uint16_t* modeReg) {
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &WRITE_MODE_REG, 1, TIMEOUT);
	HAL_SPI_Transmit(&hspi1, (uint8_t*) modeReg, 2, TIMEOUT);
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);

	HAL_Delay(READ_DELAY);

}

void PTADC_WriteModeReg(uint16_t* modeReg) {
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &WRITE_MODE_REG, 1, TIMEOUT);

	HAL_SPI_Transmit(&hspi1, (uint8_t*) &modeReg, 2, TIMEOUT);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);
}

uint32_t PTADC_GetConversionResult() {
	uint32_t result = 0xFF;
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &READ_DATA_REG, 1, TIMEOUT);
	HAL_SPI_Receive(&hspi1, (uint8_t*) &result, 3, TIMEOUT);
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);

	return result;
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
	PTADC_ResetPT();
	uartPrint((uint8_t*)"Conversion Ready \n");
	uint32_t temp = PTADC_GetRawTempFromChannel(PT_CHANNEL_1);
	uint8_t printout[BUFSIZ] = {0};

	float volts = temp * 2.5 / (powf(2, 24));
	snprintf(printout, BUFSIZ, "Volts: %0.2f\n", volts);
	uartPrint(printout);
	for (int i = 0; i < 4; i++)
		uartPrintBinary8(((uint8_t*)&temp)[i], 0);
	uartPrint((uint8_t*)"\r\n");
}
