drv_modules = TIMER INTRPT GPIO DMA CLOCK ADC
bsw_modules = PRINT
app_modules = LEDApp
base_modules = $(SRC_DIR)
modules = $(base_modules) \
          $(addprefix $(SRC_DIR)/Drivers/,$(drv_modules)) \
		  $(addprefix $(SRC_DIR)/Bsw/,$(bsw_modules)) \
		  $(addprefix $(SRC_DIR)/Appl/,$(app_modules))

-include $(addsuffix /module.mk,$(modules))
# -include $(SRC_DIR)/Drivers/TIMER/module.mk
# -include $(SRC_DIR)/Drivers/INTRPT/module.mk
# -include $(SRC_DIR)/Drivers/GPIO/module.mk
# -include $(SRC_DIR)/Drivers/DMA/module.mk
# -include $(SRC_DIR)/Drivers/CLOCK/module.mk
# -include $(SRC_DIR)/Drivers/ADC/module.mk
# -include $(SRC_DIR)/Bsw/PRINT/module.mk
# -include $(SRC_DIR)/Appl/LEDApp/module.mk
# -include $(SRC_DIR)/module.mk

## --------------------------------------------------------------------------
# End of Makefile