/**
  ******************************************************************************
  * File Name          : main.hpp
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

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
#define TC_CS4_Pin GPIO_PIN_0
#define TC_CS4_GPIO_Port GPIOD
#define TC_CS3_Pin GPIO_PIN_1
#define TC_CS3_GPIO_Port GPIOD
#define TC_CS2_Pin GPIO_PIN_2
#define TC_CS2_GPIO_Port GPIOD
#define TC_CS1_Pin GPIO_PIN_3
#define TC_CS1_GPIO_Port GPIOD
#define PT_CS_Pin GPIO_PIN_4
#define PT_CS_GPIO_Port GPIOD

// Global Vars
#define TIMEOUT 10000

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
 #define USE_FULL_ASSERT    1U 

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
