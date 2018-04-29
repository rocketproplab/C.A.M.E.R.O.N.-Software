################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/init/gpio.c \
../Src/init/i2c.c \
../Src/init/spi.c \
../Src/init/stm32f4xx_hal_msp.c \
../Src/init/stm32f4xx_it.c \
../Src/init/system_stm32f4xx.c \
../Src/init/usart.c 

OBJS += \
./Src/init/gpio.o \
./Src/init/i2c.o \
./Src/init/spi.o \
./Src/init/stm32f4xx_hal_msp.o \
./Src/init/stm32f4xx_it.o \
./Src/init/system_stm32f4xx.o \
./Src/init/usart.o 

C_DEPS += \
./Src/init/gpio.d \
./Src/init/i2c.d \
./Src/init/spi.d \
./Src/init/stm32f4xx_hal_msp.d \
./Src/init/stm32f4xx_it.d \
./Src/init/system_stm32f4xx.d \
./Src/init/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/init/%.o: ../Src/init/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -I"C:/Users/Ayilay/Documents/SystemWorkbench/CAMREON-Test/Inc" -I"C:/Users/Ayilay/Documents/SystemWorkbench/CAMREON-Test/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ayilay/Documents/SystemWorkbench/CAMREON-Test/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Ayilay/Documents/SystemWorkbench/CAMREON-Test/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ayilay/Documents/SystemWorkbench/CAMREON-Test/Drivers/CMSIS/Include"  -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


