################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Drivers/GPIO/GPIO.c 

OBJS += \
./src/Drivers/GPIO/GPIO.o 

C_DEPS += \
./src/Drivers/GPIO/GPIO.d 


# Each subdirectory must supply rules for building sources it contributes
src/Drivers/GPIO/GPIO.o: ../src/Drivers/GPIO/GPIO.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L476xx -c -I../src -I../src/Drivers/CMSIS/Include -I../src/Drivers/STM32L4xx_HAL_Driver/Inc -I../src/Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../src/Drivers/GPIO -I../src/Drivers/TIMER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/Drivers/GPIO/GPIO.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

