/*
 * 	File: thermocouple.c
 *
 * 	Helper functions to interface with the Thermocouples
 *
 * 	Author: George Troulis
 */

#include <stdbool.h>

#include "init/gpio.h"
#include "init/spi.h"
#include "init/usart.h"
#include "thermocouple.h"

/**
 * Tests the 1nd Thermocouple (no reason why we chose the 2nd one)
 */
void testTC1() {

	uint8_t rxBuf[4] = { 0 };

	HAL_GPIO_WritePin(TC_CS1_GPIO_Port, TC_CS1_Pin, GPIO_PIN_RESET);
	//requires 32 bit buffer
	//rxBuf[31] is sign bit, rxBuf[30:18] are TC temperature(signed value)
	//rxBuf[15:4] is reference voltage
	HAL_SPI_Receive(&hspi1, rxBuf, (uint16_t) 4, TIMEOUT);

	HAL_GPIO_WritePin(TC_CS1_GPIO_Port, TC_CS1_Pin, GPIO_PIN_SET);

	for (int i = 0; i < 4; i++) {
		uartPrintBinary8(rxBuf[i], false);
		uartPrint(" ");
	}
	uartPrint("\r\n");
	int32_t sval = 0;
	uint32_t val = 0;
	for (int i = 0; i < 4; i++) {
		val |= rxBuf[i] << (3-i)*8;

		uartPrintBinary8(((uint8_t*) &val)[3-i], 1);
	}

	sval = val >> (32 - 14);

	char buf[10] = { '\0' };
	snprintf(buf, 10, "%4.02f\r\n", (float) sval / 4);
	uartPrint(buf);

}
