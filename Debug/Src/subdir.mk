################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/ptadc.c 

OBJS += \
./Src/main.o \
./Src/ptadc.o 

C_DEPS += \
./Src/main.d \
./Src/ptadc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -I"C:/Users/Ayilay/Documents/SystemWorkbench/CAMREON-Test/Inc" -I"C:/Users/Ayilay/Documents/SystemWorkbench/CAMREON-Test/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ayilay/Documents/SystemWorkbench/CAMREON-Test/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Ayilay/Documents/SystemWorkbench/CAMREON-Test/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ayilay/Documents/SystemWorkbench/CAMREON-Test/Drivers/CMSIS/Include"  -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


