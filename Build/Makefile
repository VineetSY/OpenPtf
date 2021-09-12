## --------------------------------------------------------------------------
## PROJECT   : OpenPtf
## MAKE      : GNU make
## PURPOSE   : Makefile for project compilation and analysis
## TARGET    : STM32L476RG
## COMPILER  : GNU Tools for STM32
## COPYRIGHT : (c) 2021 Vineet Yadav
## REMARKS   :
## REVISION  :
## --------------------------------------------------------------------------
all:

# Custom functions
# $(subdirectory)
subdirectory = $(patsubst $(SRC_DIR)/%/module.mk,%, \
                 $(word \
                   $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))
# Include files
include config.mk
include modules.mk

# Add all include dirs to vpath to search for c source files
vpath %.c $(include_dirs)
vpath %.s $(include_dirs)
## Available Targets:
## * all		:Build everything
.PHONY : all
all : $(BIN)

# Rule for building main binary
$(BIN) : $(OBJS)
	@echo "-------------------------build elf----------------------------------------------"
	$(CC) $(CFLAGS) $(OBJS) -o $@

# rule for compiling C files
# $(OBJS) : $(SRCS)
$(OBJ_DIR)/%.o : %.c
# this whole recipe is wrong, but right now only this works.
	@echo Building $<
	$(CC) $< $(CFLAGS) -c $(addprefix -I,$(include_dirs)) $(CC_DEP) -o $@
# %.o : $(SRC_DIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# rule for compiling assembly files
$(OBJ_DIR)/%.o: %.s
	@echo "--------------------------asm start-------------------------------------------------"
	$(CC) $(ASFLAGS) -o "$@" "$<"
	@echo "---------------------------asm end------------------------------------------------"


## * clean	:Remove all from the results dir
clean :
	rm -rf $(BIN_DIR)/* $(OBJ_DIR)/* $(DEP_DIR)/*

# Help will read this makefile itself and look for comments that start with ##
.PHONY : help
help : Makefile
# Comments for users should start with ##, below command will read these comments
	@sed -n 's/^##//p' $<

.PHONY : test
test :
	@echo $(CPP)
	@echo "---------------------------------------------------------------------------"

## --------------------------------------------------------------------------
# End of Makefile