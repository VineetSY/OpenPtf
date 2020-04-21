################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../src/startup_stm32l476xx.s 

C_SRCS += \
../src/main.c \
../src/system_stm32l4xx.c \
../src/tiny_printf.c 

OBJS += \
./src/main.o \
./src/startup_stm32l476xx.o \
./src/system_stm32l4xx.o \
./src/tiny_printf.o 

C_DEPS += \
./src/main.d \
./src/system_stm32l4xx.d \
./src/tiny_printf.d 


# Each subdirectory must supply rules for building sources it contributes
src/main.o: ../src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L476xx -c -I../src -I../src/Drivers/CMSIS/Include -I../src/Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../src/Drivers/GPIO -I../src/Drivers/TIMER -I../src/Drivers/INTRPT -I../src/Drivers/CLOCK -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/%.o: ../src/%.s
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DSTM32L476xx -c -I../src -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -x assembler-with-cpp --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
src/system_stm32l4xx.o: ../src/system_stm32l4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L476xx -c -I../src -I../src/Drivers/CMSIS/Include -I../src/Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../src/Drivers/GPIO -I../src/Drivers/TIMER -I../src/Drivers/INTRPT -I../src/Drivers/CLOCK -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/system_stm32l4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/tiny_printf.o: ../src/tiny_printf.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L476xx -c -I../src -I../src/Drivers/CMSIS/Include -I../src/Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../src/Drivers/GPIO -I../src/Drivers/TIMER -I../src/Drivers/INTRPT -I../src/Drivers/CLOCK -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/tiny_printf.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

