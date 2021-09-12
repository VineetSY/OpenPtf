## Filename : config.mk

# --------------------------------------------------------------------------- #
# Tools
CC:=arm-none-eabi-gcc

# --------------------------------------------------------------------------- #
# Compile flags and options
# Machine architecture
MACH=cortex-m4
# Debug Level - using max level
DBG_LVL:=-g3
# Language Standard - Selecting C11 standard
LANG_STD:=gnu11
# Define Symbols
TARGET:=STM32L476xx
# Optimization level
OPT_LVL:=-O0
# Functions in their own sections
FUNC_SECT:=-ffunction-sections
# Data their in own sections
DATA_SECT:=-fdata-sections
# Compiler warning level
WARN_LVL:=-Wall
# Stack usage analysis
STK_USG:=-fstack-usage
# gcc specs file
CC_SPCS:=--specs=nano.specs
# Floating Point unit
FPU:=-mfpu=fpv4-sp-d16
# Floating point ABI
FPU_ABI:=-mfloat-abi=hard
# Instruction Set
ISA:=-mthumb
# Flags for generating dependency files from compiler
CC_DEP=-MMD -MP -MF"$(DEP_DIR)/$*.d" -MT"$(OBJ_DIR)/$*.o" $(CC_SPCS) $(FPU) $(FPU_ABI) $(ISA)
# Extra flags to give to the C compiler.
CFLAGS:=-mcpu=$(MACH) -std=$(LANG_STD) $(DBG_LVL) -D$(TARGET) $(OPT_LVL) $(FUNC_SECT) $(DATA_SECT) $(WARN_LVL) $(STK_USG)
# Extra flags to give to the C preprocessor
CPPFLAGS:= 
# Extra flags to give to the assembler
ASFLAGS=-mcpu=$(MACH) $(DBG_LVL) -DSTM32L476xx -c -I../src -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -x assembler-with-cpp -MMD -MP -MF"$(DEP_DIR)/$*.d" -MT"$(OBJ_DIR)/$*.o" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb
# Extra flags to give to compilers when they are supposed to invoke the linker
LDFLAGS:=
# --------------------------------------------------------------------------- #
# Directories and paths
# Source Directory
SRC_DIR:=../src
# SRC_DIR:=/home/vineet/Workspace/OpenPtf/src
# Objects Directory
OBJ_DIR:=./obj
# OBJ_DIR:=/home/vineet/Workspace/OpenPtf/Build/obj
# Dependencies Directory
DEP_DIR:=./dep
# DEP_DIR:=/home/vineet/Workspace/OpenPtf/Build/dep
# Binary Directory
BIN_DIR:=./bin
# BIN_DIR:=/home/vineet/Workspace/OpenPtf/Build/bin

# --------------------------------------------------------------------------- #
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
DEPS:=$(OBJS:.o=.d)
# DEPS:=$(addprefix $(DEP_DIR)/,$(notdir $(patsubst %.o, %.d, $(OBJS))))
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

## --------------------------------------------------------------------------
# End of Makefile