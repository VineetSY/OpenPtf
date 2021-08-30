## Filename : config.mk
CC:=arm-none-eabi-gcc
# CFLAGS:=-mcpu=cortex-m4 -std=gnu11 -g3
CFLAGS:=-mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L476xx
unknown_flags:=-O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"/home/vineet/Workspace/OpenPtf2/Build/obj/PRINT.d" -MT"/home/vineet/Workspace/OpenPtf2/Build/obj/PRINT.o" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb
SRC_DIR:=../src
# OBJ_DIR:=./obj
BIN_DIR:=./bin
# SRC_DIR:=/home/vineet/Workspace/OpenPtf2/src
OBJ_DIR:=/home/vineet/Workspace/OpenPtf2/Build/obj
# BIN_DIR:=/home/vineet/Workspace/OpenPtf2/Build/bin
# For SRCS we will find all the files that have .c 
# extension in the SRC_DIR and assign the relative name
C_SRCS:=$(shell find $(SRC_DIR) -name '*.c')
S_SRCS:=$(shell find $(SRC_DIR) -name '*.s')
SRCS:= $(C_SRCS) $(S_SRCS)
# For OBJS we will replace all the .c extenstions
# in SRCS with .o and then take the file name part
#  without the directory part
OBJS:=$(addprefix $(OBJ_DIR)/,$(notdir $(patsubst %.c, %.o, $(SRCS)) $(patsubst %.s, %.o, $(SRCS))))
# OBJS:=$(notdir $(patsubst %.c, %.o, $(SRCS)))
BIN:=$(BIN_DIR)/OpenPtf.bin
ELF:=$(BIN_DIR)/OpenPtf.elf
include_dirs:=../src \
              ../src/Drivers/CMSIS/Include \
			  ../src/Drivers/CMSIS/Device/ST/STM32L4xx/Include \
			  ../src/Drivers/GPIO \
			  ../src/Drivers/TIMER \
			  ../src/Drivers/INTRPT \
			  ../src/Drivers/CLOCK \
			  ../src/Appl/LEDApp \
			  ../src/Bsw/PRINT \
			  ../src/Drivers/ADC \
			  ../src/Drivers/DMA
