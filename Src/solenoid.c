/*
 * 	File: solenoid.c
 *
 * 	Helper functions to interface with the Solenoids
 *
 * 	Author: George Troulis
 */
#include "solenoid.h"
#include "init/gpio.h"
#include "init/usart.h"


void testSol5() {
	uartPrint((uint8_t*) "Solenoid On");
	HAL_GPIO_WritePin(SOL_OUT5_GPIO_Port, SOL_OUT5_Pin, GPIO_PIN_SET);
	HAL_Delay(2000);

	uartPrint((uint8_t*) "Solenoid Off\r\n");
	HAL_GPIO_WritePin(SOL_OUT5_GPIO_Port, SOL_OUT5_Pin, GPIO_PIN_RESET);
	HAL_Delay(2000);
}
