/*
* 	File: ptadc.h
 *
 * 	Helper functions for the AD7794 ADC on CAMERON
 *
 * 	Author: George Troulis
 *
 * 	Ported from juliano77's Arduino library:
 * 	https://github.com/jjuliano77/JJ_AD7794
 */

#ifndef PTADC_H
#define PTADC_H

#define PT_CHANNEL_1 0
#define PT_CHANNEL_2 1
#define PT_CHANNEL_3 2
#define PT_CHANNEL_4 3
#define PT_CHANNEL_5 4

#define READ_DELAY 10

// Register values for writing
uint16_t modeReg;

void PTADC_Init();
void PTADC_Reset();
uint8_t PTADC_ReadStatusRegister();
uint32_t PTADC_GetRawTempFromChannel(uint8_t channel);

void PTADC_SetActiveChannel(uint8_t channel);
void PTADC_WriteConfReg(uint8_t* confReg);
void PTADC_StartConversion(uint16_t* modeReg);
uint32_t PTADC_GetConversionResult();

void testADC();

#endif
