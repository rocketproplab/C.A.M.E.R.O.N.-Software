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

#define PTADC_CHANNEL_1 	0
#define PTADC_CHANNEL_2 	1
#define PTADC_CHANNEL_3 	2
#define PTADC_CHANNEL_4 	3
#define PTADC_CHANNEL_5 	4

#define PTADC_BIPOLAR  		0
#define PTADC_UNIPOLAR 		1

#define PTADC_NOT_BUFFERED  0
#define PTADC_BUFFERED  	1

#define PTADC_MODE_CONTINUOUS_CONV	0
#define PTADC_MODE_SINGLE_CONV		1

								// (With 2.5V Reference)
#define PTADC_GAIN_1	0x00	// InputRange: 2.5V
#define PTADC_GAIN_2	0x01	// InputRange: 1.25V
#define PTADC_GAIN_4	0x02	// InputRange: 625mV
#define PTADC_GAIN_8	0x03	// InputRange: 312.5mV
#define PTADC_GAIN_16	0x04	// InputRange: 156.2mV
#define PTADC_GAIN_32	0x05	// InputRange: 78.125mV
#define PTADC_GAIN_64	0x06	// InputRange: 39.06mV
#define PTADC_GAIN_128	0x07	// InputRange: 19.53mV

									// 		  (Hz)			  (ms)
#define PTADC_UPDATE_RATE_0		 0	// F_adc= x,	T_settle= x
#define PTADC_UPDATE_RATE_1		 1	// F_adc= 470,	T_settle= 4
#define PTADC_UPDATE_RATE_2		 2	// F_adc= 242,	T_settle= 8
#define PTADC_UPDATE_RATE_3		 3	// F_adc= 123, 	T_settle= 16
#define PTADC_UPDATE_RATE_4		 4	// F_adc= 62, 	T_settle= 32
#define PTADC_UPDATE_RATE_5		 5	// F_adc= 50, 	T_settle= 40
#define PTADC_UPDATE_RATE_6		 6	// F_adc= 39, 	T_settle= 48
#define PTADC_UPDATE_RATE_7		 7	// F_adc= 33.2,	T_settle= 60
#define PTADC_UPDATE_RATE_8		 8	// F_adc= 19.6,	T_settle= 101
#define PTADC_UPDATE_RATE_9		 9	// F_adc= 16.7,	T_settle= 120
#define PTADC_UPDATE_RATE_10	 1	// F_adc= 16.7,	T_settle= 120
#define PTADC_UPDATE_RATE_11	 1	// F_adc= 12.5,	T_settle= 160
#define PTADC_UPDATE_RATE_12	 1	// F_adc= 10, 	T_settle= 200
#define PTADC_UPDATE_RATE_13	 1	// F_adc= 8.33,	T_settle= 240
#define PTADC_UPDATE_RATE_14	 1	// F_adc= 6.25,	T_settle= 320
#define PTADC_UPDATE_RATE_15	 1	// F_adc= 4.17,	T_settle= 480

#define READ_DELAY 10

// Public Interface Functions
void PTADC_Init();
void PTADC_Reset();
uint32_t PTADC_GetRawTempFromChannel(uint8_t channel);

// Update Settings Functions
void PTADC_SetActiveChannel(uint8_t channel);
void PTADC_SetGain(uint8_t gainOpt);
void PTADC_SetIsBuffered(uint8_t isBufferedOpt);
void PTADC_SetIsUnipolar(uint8_t isUnipolarOpt);
void PTADC_SetUpdateRate(uint8_t updateRateOpt);
void PTADC_SetADCMode(uint8_t adcModeOpt);

// Register Read Functions
uint8_t	 PTADC_ReadStatReg();
uint16_t PTADC_ReadModeReg();
uint16_t PTADC_ReadConfReg();

// Register Write Functions
void PTADC_WriteConfReg();
void PTADC_WriteModeReg();

#endif
