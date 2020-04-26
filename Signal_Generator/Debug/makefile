################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/TIMER/subdir.mk
-include MCAL/MCU_POWER/subdir.mk
-include MCAL/G_INTERRUPT/subdir.mk
-include MCAL/EXT_INTERRUPT/subdir.mk
-include MCAL/DIO/subdir.mk
-include FIRMWARE_SERVICE/TMU/subdir.mk
-include FIRMWARE_SERVICE/SOS/subdir.mk
-include FIRMWARE_SERVICE/PWM/subdir.mk
-include ECUAL/LEDs/subdir.mk
-include APP/TMU_APP/subdir.mk
-include APP/SOS_APP/subdir.mk
-include APP/PWM_APP/subdir.mk
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
Signal_Generator.lss \

FLASH_IMAGE += \
Signal_Generator.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: Signal_Generator.elf secondary-outputs

# Tool invocations
Signal_Generator.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Signal_Generator.map -mmcu=atmega32 -o "Signal_Generator.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Signal_Generator.lss: Signal_Generator.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Signal_Generator.elf  >"Signal_Generator.lss"
	@echo 'Finished building: $@'
	@echo ' '

Signal_Generator.hex: Signal_Generator.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Signal_Generator.elf  "Signal_Generator.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Signal_Generator.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Signal_Generator.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: Signal_Generator.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm32 -cusbasp -Uflash:w:Signal_Generator.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Signal_Generator.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
