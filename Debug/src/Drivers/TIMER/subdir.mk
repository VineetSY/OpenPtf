################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Drivers/TIMER/TIMER.c 

OBJS += \
./src/Drivers/TIMER/TIMER.o 

C_DEPS += \
./src/Drivers/TIMER/TIMER.d 


# Each subdirectory must supply rules for building sources it contributes
src/Drivers/TIMER/TIMER.o: ../src/Drivers/TIMER/TIMER.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L476xx -c -I../src -I../src/Drivers/CMSIS/Include -I../src/Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../src/Drivers/GPIO -I../src/Drivers/TIMER -I../src/Drivers/INTRPT -I../src/Drivers/CLOCK -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/Drivers/TIMER/TIMER.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

