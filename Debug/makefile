################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/Drivers/TIMER/subdir.mk
-include src/Drivers/GPIO/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
OpenPtf.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
OpenPtf.list \

OBJCOPY_BIN += \
OpenPtf.bin \


# All Target
all: OpenPtf.elf secondary-outputs

# Tool invocations
OpenPtf.elf: $(OBJS) $(USER_OBJS) ../Build/stm32l4_flash.ld
	arm-none-eabi-gcc -o "OpenPtf.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"../Build/stm32l4_flash.ld" --specs=nosys.specs -Wl,-Map="OpenPtf.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

OpenPtf.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "OpenPtf.list"
	@echo 'Finished building: $@'
	@echo ' '

OpenPtf.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "OpenPtf.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
