######################################################################################################
TARGET_SEL = -mcpu=cortex-m0plus
TGTFLAGS =  $(TARGET_SEL)
######################################################################################################

PSOC6_TARGET = out/psoc6_cm0

BIN2C = python ../../cat1cm0p/bin2c.py

ASMFILE1 = ../../mtb-pdl-cat1/devices/COMPONENT_CAT1A/templates/COMPONENT_MTB/COMPONENT_CM0P/TOOLCHAIN_GCC_ARM/startup_psoc6_02_cm0plus.S
ASMFILE2 = ../../mtb-pdl-cat1/drivers/source/TOOLCHAIN_GCC_ARM/cy_syslib_gcc.S

# C source files
CFILES += \
	 ../../mtb-pdl-cat1/devices/COMPONENT_CAT1A/source/cy_device.c	\
	 ../../mtb-pdl-cat1/devices/COMPONENT_CAT1A/templates/COMPONENT_MTB/COMPONENT_CM0P/system_psoc6_cm0plus.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_ipc_pipe.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_ipc_drv.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_ipc_sema.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_wdt.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_sysint.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_sysclk.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_gpio.c	\
	 ../../mtb-pdl-cat1/drivers/source/cy_syslib.c	\
	 main.c

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
	-DCY8C624ABZI_S2D44


PSOC6_LD = ../../mtb-pdl-cat1/devices/COMPONENT_CAT1A/templates/COMPONENT_MTB/COMPONENT_CM0P/TOOLCHAIN_GCC_ARM/cy8c6xxa_cm0plus.ld

OBJECTS += \
	out/cy_device.o 	\
	out/cy_ipc_pipe.o	\
	out/cy_ipc_drv.o	\
	out/cy_ipc_sema.o	\
	out/cy_wdt.o	\
	out/cy_sysint.o	\
	out/cy_sysclk.o	\
	out/system_psoc6_cm0plus.o 	\
	out/startup_psoc6_02_cm0plus.o 	\
	out/cy_gpio.o	\
	out/cy_syslib.o	\
	out/cy_syslib_gcc.o	\
	out/main.o

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
	 $(AS) $(AFLAGS) $(ASMFILE1) -o out/startup_psoc6_02_cm0plus.o
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
	$(LD) -Wl,--start-group $(TARGET_SEL) -mthumb --entry=cy_m0p_image -Wl,-Map,$(PSOC6_TARGET).map -T $(PSOC6_LD) -specs=nano.specs -Wl,--gc-sections -g -ffunction-sections -finline-functions -Os -Wl,--end-group -o $(PSOC6_TARGET).elf $(OBJECTS) 

$(PSOC6_TARGET).hex : $(PSOC6_TARGET).elf
	@echo "-------------------------"
	@echo "Building the hex file" $@
	@echo "-------------------------"
	$(OC) -O ihex $(PSOC6_TARGET).elf $(PSOC6_TARGET).hex
	$(OC) -O binary $(PSOC6_TARGET).elf $(PSOC6_TARGET).bin
	$(BIN2C) $(PSOC6_TARGET).bin $(PSOC6_TARGET).c
	@echo "-------------------------"
	@echo "Building the list file" $@
	@echo "--------------------------"
	arm-none-eabi-objdump -S $(PSOC6_TARGET).elf > $(PSOC6_TARGET).lst
