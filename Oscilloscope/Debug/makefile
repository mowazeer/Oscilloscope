################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/G_INTERRUPT/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include ECUAL/LCD_TFT_ili9486/subdir.mk
-include APP/Osc_App/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Oscilloscope.lss \

FLASH_IMAGE += \
Oscilloscope.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: Oscilloscope.elf secondary-outputs

# Tool invocations
Oscilloscope.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Oscilloscope.map -mmcu=atmega32 -o "Oscilloscope.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Oscilloscope.lss: Oscilloscope.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Oscilloscope.elf  >"Oscilloscope.lss"
	@echo 'Finished building: $@'
	@echo ' '

Oscilloscope.hex: Oscilloscope.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Oscilloscope.elf  "Oscilloscope.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Oscilloscope.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Oscilloscope.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: Oscilloscope.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm32 -cusbasp -Uflash:w:Oscilloscope.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Oscilloscope.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
