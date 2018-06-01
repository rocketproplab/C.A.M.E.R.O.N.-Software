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

static void PTADC_BuildModeReg();
static void PTADC_BuildConfReg();

const uint8_t READ_STATUS_REG = 0x40;
const uint8_t READ_MODE_REG   = 0x48;
const uint8_t READ_CONF_REG   = 0x50;
const uint8_t READ_DATA_REG   = 0x58;

const uint8_t WRITE_MODE_REG  = 0x08;
const uint8_t WRITE_CONF_REG  = 0x10;

// Register values for writing
uint8_t modeReg[2];
uint8_t confReg[2];

// Conf Reg Options
static uint8_t currentChannel;
static uint8_t isUnipolar;
static uint8_t isBuffered;
static uint8_t gain;

// Mode Reg Options
static uint8_t adcMode;
static uint8_t updateRate;

////////////////////////////////////////////////////////////////////////////////
//	High Level interface functions
////////////////////////////////////////////////////////////////////////////////

void PTADC_Init() {
	gain = PTADC_GAIN_1;
	updateRate = PTADC_UPDATE_RATE_0;
	isUnipolar = PTADC_BIPOLAR;
	isBuffered = PTADC_BUFFERED;
	currentChannel = PTADC_CHANNEL_1;

	PTADC_BuildModeReg();
	PTADC_BuildConfReg();
}

void PTADC_Reset() {
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	uint32_t ADC_DATA_RESET = (uint32_t) (~0);
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &ADC_DATA_RESET, 4, TIMEOUT);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);
}

uint32_t PTADC_GetRawTempFromChannel(uint8_t channel) {

	PTADC_SetActiveChannel(channel);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
//	Option Set Functions
////////////////////////////////////////////////////////////////////////////////

void PTADC_SetGain(uint8_t gainOpt) {
	gain = gainOpt;

	PTADC_BuildConfReg();
	PTADC_WriteConfReg();
}

void PTADC_SetActiveChannel(uint8_t channel) {
	currentChannel = channel;

	PTADC_BuildConfReg();
	PTADC_WriteConfReg(confReg);
}

void PTADC_SetIsBuffered(uint8_t isBufferedOpt) {
	isBuffered = isBufferedOpt;

	PTADC_BuildConfReg();
	PTADC_WriteConfReg();
}

void PTADC_SetIsUnipolar(uint8_t isUnipolarOpt) {
	isUnipolar = isUnipolarOpt;

	PTADC_BuildConfReg();
	PTADC_WriteConfReg();
}

void PTADC_SetUpdateRate(uint8_t updateRateOpt) {
	updateRate = updateRateOpt;

	PTADC_BuildModeReg();
	PTADC_WriteModeReg();
}

void PTADC_SetADCMode(uint8_t adcModeOpt) {
	adcMode = adcModeOpt;

	PTADC_BuildModeReg();
	PTADC_WriteModeReg();
}

////////////////////////////////////////////////////////////////////////////////
//	Register Write Functions
////////////////////////////////////////////////////////////////////////////////

void PTADC_WriteConfReg() {
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &WRITE_CONF_REG, 1, TIMEOUT);
	HAL_SPI_Transmit(&hspi1, confReg, 2, TIMEOUT);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);
}

void PTADC_WriteModeReg() {
	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &WRITE_MODE_REG, 1, TIMEOUT);
	HAL_SPI_Transmit(&hspi1, modeReg, 2, TIMEOUT);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);
}

////////////////////////////////////////////////////////////////////////////////
//	Register Builder functions
////////////////////////////////////////////////////////////////////////////////

static void PTADC_BuildConfReg() {
	uint16_t confRegBuf = 0;
	confRegBuf |= currentChannel;
	confRegBuf |= gain << 8;
	confRegBuf = isUnipolar ? (confRegBuf | 1<<12) : (confRegBuf & ~(1<<12));
	confRegBuf = isBuffered ? (confRegBuf | 1<<4) : (confRegBuf & ~(1<<4));

	confReg[0] = (uint8_t) ((confRegBuf & 0xFF00) >> 8);
	confReg[1] = (uint8_t) (confRegBuf & 0x00FF);
}

static void PTADC_BuildModeReg() {
	uint16_t modeRegBuf = 0;
	modeRegBuf |= updateRate;
	modeRegBuf |= (adcMode << 13);

	modeReg[0] = (uint8_t) ((modeRegBuf & 0xFF00) >> 8);
	modeReg[1] = (uint8_t) (modeRegBuf & 0x00FF);
}

////////////////////////////////////////////////////////////////////////////////
//	Register Read functions
////////////////////////////////////////////////////////////////////////////////

uint8_t PTADC_ReadStatReg() {
	uint8_t rxResult = 0;

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &READ_STATUS_REG, 1, TIMEOUT);
	HAL_SPI_Receive(&hspi1, &rxResult, 1, TIMEOUT);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);

	return rxResult;
}

uint16_t PTADC_ReadModeReg() {
	uint8_t rxResult[2];

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &READ_MODE_REG, 1, TIMEOUT);
	HAL_SPI_Receive(&hspi1, rxResult, 2, TIMEOUT);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);

	uint16_t rxResultBuf = rxResult[0] | (rxResult[1] << 8);

	return rxResultBuf;
}

uint16_t PTADC_ReadConfReg() {
	uint8_t rxResult[2];

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &READ_CONF_REG, 1, TIMEOUT);
	HAL_SPI_Receive(&hspi1, rxResult, 2, TIMEOUT);

	HAL_GPIO_WritePin(PT_CS_GPIO_Port, PT_CS_Pin, GPIO_PIN_SET);

	uint16_t rxResultBuf = rxResult[0] | (rxResult[1] << 8);

	return rxResultBuf;
}
