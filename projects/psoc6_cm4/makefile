######################################################################################################
TARGET_SEL = -mcpu=cortex-m4
TGTFLAGS = $(TARGET_SEL) -mfpu=fpv4-sp-d16 
######################################################################################################

PSOC6_TARGET = out/hello_world

ASMFILES = ../../psoc6pdl/devices/templates/COMPONENT_MTB/COMPONENT_CM4/TOOLCHAIN_GCC_ARM/startup_psoc6_02_cm4.S

# ASM source files
ASMFILES += \
	   ../../psoc6pdl/drivers/source/TOOLCHAIN_GCC_ARM/cy_syslib_gcc.S

# C source files
CFILES += \
	 ../../cat1cm0p/COMPONENT_CAT1A/COMPONENT_CM0P_SLEEP/psoc6_02_cm0p_sleep.c	\
	 ../../psoc6pdl/devices/templates/COMPONENT_MTB/COMPONENT_CM4/system_psoc6_cm4.c	\
	 ../../psoc6pdl/drivers/source/cy_gpio.c	\
	 ../../psoc6pdl/drivers/source/cy_syslib.c	\
	 main_cm4.c

# Assembler command line arguments.
AFLAGS = -c $(TARGET_SEL) --specs=nano.specs -mfloat-abi=softfp \
	 -mthumb -ffunction-sections -fdata-sections -g

# Compiler command line arguments.
CFLAGS = \
	-Os --specs=nano.specs -Og -mfloat-abi=softfp $(TGTFLAGS) \
	-mthumb -ffunction-sections -fdata-sections -g \
	-I. \
	-I../../../core-lib/include \
	-I../../../psoc6pdl/devices/include \
	-I../../../psoc6pdl/cmsis/include \
	-I../../../psoc6pdl/devices/templates/COMPONENT_MTB \
	-I../../../psoc6pdl/drivers/include \
	-DCY8C624ABZI-S2D44

PSOC6_LD = ../../TARGET_CY8CPROTO-062-4343W/COMPONENT_CM4/TOOLCHAIN_GCC_ARM/linker.ld

OBJECTS += \
	out/psoc6_02_cm0p_sleep.o \
	out/cy_syslib_gcc.o \
	out/startup_psoc6_02_cm4.o 	\
	out/cy_gpio.o 	\
	out/cy_syslib.o 	\
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
	 $(AS) $(AFLAGS) ../../TARGET_CY8CPROTO-062-4343W/COMPONENT_CM4/TOOLCHAIN_GCC_ARM/startup_psoc6_02_cm4.S -o out/startup_psoc6_02_cm4.o
	 $(AS) $(AFLAGS) ../../psoc6pdl/drivers/source/TOOLCHAIN_GCC_ARM/cy_syslib_gcc.s -o out/cy_syslib_gcc.o
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
