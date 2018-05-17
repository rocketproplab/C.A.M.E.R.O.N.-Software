/*
 * 	File: solenoid.c
 *
 * 	Helper functions to interface with the Solenoids
 *
 * 	Author: George Troulis
 */

#ifndef SOLENOID_H
#define SOLENOID_H

#define SOL_OUT5_Pin GPIO_PIN_11
#define SOL_OUT5_GPIO_Port GPIOD
#define SOL_OUT4_Pin GPIO_PIN_12
#define SOL_OUT4_GPIO_Port GPIOD
#define SOL_OUT3_Pin GPIO_PIN_13
#define SOL_OUT3_GPIO_Port GPIOD
#define SOL_OUT2_Pin GPIO_PIN_14
#define SOL_OUT2_GPIO_Port GPIOD
#define SOL_OUT1_Pin GPIO_PIN_15
#define SOL_OUT1_GPIO_Port GPIOD
#define SOL_FAULT5_Pin GPIO_PIN_8
#define SOL_FAULT5_GPIO_Port GPIOC
#define SOL_FAULT4_Pin GPIO_PIN_9
#define SOL_FAULT4_GPIO_Port GPIOC
#define SOL_FAULT3_Pin GPIO_PIN_8
#define SOL_FAULT3_GPIO_Port GPIOA
#define SOL_FAULT2_Pin GPIO_PIN_9
#define SOL_FAULT2_GPIO_Port GPIOA
#define SOL_FAULT1_Pin GPIO_PIN_10
#define SOL_FAULT1_GPIO_Port GPIOA

void testSol5();

#endif
