################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/init/ptadc.c 

OBJS += \
./Inc/init/ptadc.o 

C_DEPS += \
./Inc/init/ptadc.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/init/%.o: ../Inc/init/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -I"C:/Users/Ayilay/Documents/SystemWorkbench/CAMREON-Test/Inc" -I"C:/Users/Ayilay/Documents/SystemWorkbench/CAMREON-Test/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ayilay/Documents/SystemWorkbench/CAMREON-Test/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Ayilay/Documents/SystemWorkbench/CAMREON-Test/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ayilay/Documents/SystemWorkbench/CAMREON-Test/Drivers/CMSIS/Include"  -Og -g -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


