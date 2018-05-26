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
const uint8_t READ_STATUS_REG = 0x40;
const uint8_t WRITE_CONF_REG = 0x10;
const uint8_t WRITE_MODE_REG = 0x08;
const uint8_t READ_ID_REG = 0x60;


void PTADC_Init() {
	modeReg = 0x2001;	// Single Conversion mode, Fadc = 470Hz
}

void PTADC_Reset() {
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	uint32_t ADC_DATA_RESET = (uint32_t) (~0);
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &ADC_DATA_RESET, 4, TIMEOUT);
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);
}

uint8_t PTADC_ReadStatusRegister() {
	uint8_t rxResult[2];
	rxResult[0] = 0x27;
	rxResult[1] = 0x00;
	//PTADC_WriteConfReg(rxResult);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &READ_STATUS_REG, 1, TIMEOUT);

	HAL_SPI_Receive(&hspi1, rxResult, 1, TIMEOUT);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);

	for (int i = 0; i < 4; i++)
		uartPrintBinary8(((uint8_t*)&rxResult)[i], 0);
	uartPrint((uint8_t*)"\r\n");
	return rxResult[0];
}

uint32_t PTADC_GetRawTempFromChannel(uint8_t channel) {
	// Set the current ADC Channel
	//HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	PTADC_SetActiveChannel(channel);

	// Starts the conversion procedure by writing to the mode register, then reading the result
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);
	PTADC_StartConversion(&modeReg);
	uint32_t convResult = PTADC_GetConversionResult();
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);

	return convResult;
}

void PTADC_SetActiveChannel(uint8_t channel) {
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	// Gain = 16x (input range: 156.2 mV from datasheet)
	uint8_t gain = 0b100;
	uint16_t confReg = (gain << 8) | channel;

	PTADC_WriteConfReg(&confReg);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);
}

void PTADC_WriteConfReg(uint8_t* confReg) {
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &WRITE_CONF_REG, 1, TIMEOUT);
	HAL_SPI_Transmit(&hspi1, confReg, 2, TIMEOUT);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);
}

void PTADC_StartConversion(uint16_t* modeReg) {

	HAL_SPI_Transmit(&hspi1, &WRITE_MODE_REG, 1, TIMEOUT);
	HAL_SPI_Transmit(&hspi1, (uint8_t*) modeReg, 2, TIMEOUT);

	HAL_Delay(READ_DELAY);

}

void PTADC_WriteModeReg(uint16_t* modeReg) {
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &WRITE_MODE_REG, 1, TIMEOUT);

	HAL_SPI_Transmit(&hspi1, (uint8_t*) &modeReg, 2, TIMEOUT);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);
}

uint32_t PTADC_GetConversionResult() {
	uint32_t result = 0;
	HAL_SPI_Transmit(&hspi1, &READ_DATA_REG, 1, TIMEOUT);
	HAL_SPI_Receive(&hspi1, (uint8_t*) &result, 3, TIMEOUT);

	return result;
}

uint8_t PTADC_ReadIDRegister(){
	uint8_t result = 0;
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &READ_ID_REG, 1, TIMEOUT);
	HAL_SPI_Receive(&hspi1, (uint8_t*)&result, 1, TIMEOUT);
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);

}

void PTADC_testID(){
	uint8_t result = PTADC_ReadIDRegister();
	uartPrintBinary8(result, 0);
	uartPrint((uint8_t*)"\r\n");

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
		uartPrintBinary8(((uint8_t*)&temp)[i], 0);
	uartPrint((uint8_t*)"\r\n");
}
