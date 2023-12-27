######################################################################################################
TARGET_SEL = -mcpu=cortex-m4
TGTFLAGS = $(TARGET_SEL) -mfpu=fpv4-sp-d16 
######################################################################################################

PSOC6_TARGET = out/psoc6_cm4

ASMFILE1 = ../../mtb-pdl-cat1/devices/COMPONENT_CAT1A/templates/COMPONENT_MTB/COMPONENT_CM4/TOOLCHAIN_GCC_ARM/startup_psoc6_02_cm4.S
ASMFILE2 = ../../mtb-pdl-cat1/drivers/source/TOOLCHAIN_GCC_ARM/cy_syslib_gcc.S

# C source files
CFILES += \
	 ../psoc6_cm0/out/psoc6_cm0.c	\
	 ../../mtb-pdl-cat1/devices/COMPONENT_CAT1A/source/cy_device.c	\
	 ../../mtb-pdl-cat1/devices/COMPONENT_CAT1A/templates/COMPONENT_MTB/COMPONENT_CM4/system_psoc6_cm4.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_ipc_pipe.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_ipc_drv.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_ipc_sema.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_wdt.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_sysint.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_sysclk.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_gpio.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_syslib.c	\
	../../mtb-pdl-cat1/drivers/source/cy_scb_common.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_scb_uart.c	\
	 main_cm4.c

# Assembler command line arguments.
AFLAGS = -c $(TARGET_SEL) --specs=nano.specs -mfloat-abi=softfp \
	 -mthumb -ffunction-sections -fdata-sections -g

# Compiler command line arguments.
CFLAGS = \
	-Os --specs=nano.specs -Og -mfloat-abi=softfp $(TGTFLAGS) \
	-mthumb -ffunction-sections -fdata-sections -g \
	-I. \
	-I../../../mtb-pdl-cat1/cmsis/include \
	-I../../../mtb-pdl-cat1/devices/COMPONENT_CAT1A/include \
	-I../../../mtb-pdl-cat1/devices/COMPONENT_CAT1A/templates/COMPONENT_MTB \
	-I../../../mtb-pdl-cat1/drivers/include	\
	-I../../../core-lib/include \
	-I../../../psoc6hal/include \
	-I../../../psoc6hal/COMPONENT_PSOC6HAL/include \
	-I../../../psoc6hal/COMPONENT_PSOC6HAL/include/triggers \
	-I../../../psoc6hal/COMPONENT_PSOC6HAL/include/pin_packages \
	-I../../../retarget-io \
	-DCY8C624ABZI_S2D44 -DCY_IPC_DEFAULT_CFG_DISABLE

PSOC6_LD = ../../mtb-pdl-cat1/devices/COMPONENT_CAT1A/templates/COMPONENT_MTB/COMPONENT_CM4/TOOLCHAIN_GCC_ARM/cy8c6xxa_cm4_dual.ld

OBJECTS += \
	out/psoc6_cm0.o \
	out/startup_psoc6_02_cm4.o \
	out/cy_syslib_gcc.o \
	out/system_psoc6_cm4.o \
	out/cy_gpio.o 	\
	out/cy_syslib.o 	\
	out/cy_sysclk.o 	\
	out/cy_device.o 	\
	out/cy_scb_common.o 	\
	out/cy_scb_uart.o 	\
	out/main_cm4.o

# Path to compiler/linker tools.
CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
OC = arm-none-eabi-objcopy


DONE=@if [ -f $(1) ]; then echo Build completed.; fi
RM=rm -f $(1)

.SUFFIXES: .o .c .s
.PHONY: all clean build

all: prep ofiles $(PSOC6_TARGET).elf $(PSOC6_TARGET).hex
	$(call DONE,$(PSOC6_TARGET).hex)

rebuild: clean all

clean:
	rm -rf out
	mkdir out
prep:
	@echo '#### Prepping stuff ####'
	+(rm -rf out)
	+(mkdir out)

ofiles : $(CFILES) $(ASMFILES)
	 @echo "---------------------"
	 @echo "Building the ASM files"
	 @echo "---------------------"
	 $(AS) $(AFLAGS) $(ASMFILE1) -o out/startup_psoc6_02_cm4.o
	 $(AS) $(AFLAGS) $(ASMFILE2) -o out/cy_syslib_gcc.o
	 @echo "-------------------"
	 @echo "Building the C files"
	 @echo "-------------------"
	 for f in $(CFILES); do \
	     echo "Compiling $$f"; \
	     cd out && $(CC) $(CFLAGS) -c ../$$f && cd ..; \
	 done
	 @echo "----------------------"
	 @echo "Done compiling C files"
	 @echo "----------------------"

$(PSOC6_TARGET).elf : $(OBJECTS) $(PSOC6_LD)
	@echo "--------------------"
	@echo "Linking the elf file obj" $@
	@echo "--------------------"
	$(LD) -Wl,--start-group $(TARGET_SEL) -mthumb --entry=Reset_Handler -Wl,-Map,$(PSOC6_TARGET).map -T $(PSOC6_LD) -specs=nano.specs -Wl,--gc-sections -g -ffunction-sections -finline-functions -Os -Wl,--end-group -o $(PSOC6_TARGET).elf $(OBJECTS) 

$(PSOC6_TARGET).hex : $(PSOC6_TARGET).elf
	@echo "-------------------------"
	@echo "Building the hex file" $@
	@echo "-------------------------"
	$(OC) -O ihex $(PSOC6_TARGET).elf $(PSOC6_TARGET).hex
	@echo "-------------------------"
	@echo "Building the list file" $@
	@echo "--------------------------"
	arm-none-eabi-objdump -S $(PSOC6_TARGET).elf > $(PSOC6_TARGET).lst
