## Filename : config.mk

# Tools
CC:=arm-none-eabi-gcc

# Compile flags and options
# CFLAGS:=-mcpu=cortex-m4 -std=gnu11 -g3
# Machine architecture
MACH=cortex-m4
CFLAGS:=-mcpu=$(MACH) -std=gnu11 -g3 -DSTM32L476xx
unknown_flags:=-O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"/home/vineet/Workspace/OpenPtf/Build/obj/%.d" -MT"/home/vineet/Workspace/OpenPtf/Build/obj/%.o" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb

# Directories and paths
# Source Directory
SRC_DIR:=../src
# SRC_DIR:=/home/vineet/Workspace/OpenPtf/src
# Objects Directory
OBJ_DIR:=./obj
# OBJ_DIR:=/home/vineet/Workspace/OpenPtf/Build/obj
# Dependencies Directory
DEP_DIR:=/home/vineet/Workspace/OpenPtf/Build/dep
# Binary Directory
BIN_DIR:=./bin
# BIN_DIR:=/home/vineet/Workspace/OpenPtf/Build/bin

# File type Variables
# For SRCS we will find all the files that have .c 
# extension in the SRC_DIR and assign the relative name
# .c source files
C_SRCS:=$(shell find $(SRC_DIR) -name '*.c')
# .s (assembly) source files
S_SRCS:=$(shell find $(SRC_DIR) -name '*.s')
# List of all sources
SRCS:= $(C_SRCS) $(S_SRCS)
# For OBJS we will replace all the .c extenstions
# in C_SRCS with .o and then take the file name part
#  without the directory part, similarly for S_SRCS
# and prefix them with OBJ_DIR path
OBJS:=$(addprefix $(OBJ_DIR)/,$(notdir $(patsubst %.c, %.o, $(C_SRCS)) $(patsubst %.s, %.o, $(S_SRCS))))
# OBJS:=$(notdir $(patsubst %.c, %.o, $(SRCS)))
# For DEPS we will replace all the .o extenstions
# in OBJS with .d and then take the file name part
# without the directory part, and prefix them with
# DEP_DIR path
DEPS:=$(addprefix $(DEP_DIR)/,$(notdir $(patsubst %.o, %.d, $(OBJS))))
BIN:=$(BIN_DIR)/OpenPtf.bin
ELF:=$(BIN_DIR)/OpenPtf.elf

# include files
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
