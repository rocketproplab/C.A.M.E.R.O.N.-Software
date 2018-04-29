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

#ifndef PTADC_H_AYILAY
#define PTADC_H_AYILAY

#define PT_CHANNEL_1 0
#define PT_CHANNEL_2 1
#define PT_CHANNEL_3 2
#define PT_CHANNEL_4 3
#define PT_CHANNEL_5 4

#define READ_DELAY 10

// Register values for writing
uint16_t modeReg;

void PTADC_Init();
void PTADC_ResetPT();
uint32_t PTADC_GetRawTempFromChannel(uint8_t channel);

void PTADC_SetActiveChannel(uint8_t channel);
void PTADC_WriteConfReg(uint16_t* confReg);
void PTADC_StartConversion(uint16_t* modeReg);
uint32_t PTADC_GetConversionResult();

#endif
