################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FIRMWARE/TMU/TMU.c \
../FIRMWARE/TMU/TMU_PbCfg.c 

OBJS += \
./FIRMWARE/TMU/TMU.o \
./FIRMWARE/TMU/TMU_PbCfg.o 

C_DEPS += \
./FIRMWARE/TMU/TMU.d \
./FIRMWARE/TMU/TMU_PbCfg.d 


# Each subdirectory must supply rules for building sources it contributes
FIRMWARE/TMU/%.o: ../FIRMWARE/TMU/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\APP" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\APP\PWM_APP" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\APP\SOS_APP" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\APP\TMU_APP" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\ECUAL" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\ECUAL\LCD_4Bits" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\ECUAL\LEDs" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\FIRMWARE" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\FIRMWARE\ICU_SOFT" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\FIRMWARE\PWM" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\FIRMWARE\SOS" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\FIRMWARE\TMU" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\INFRA_STRUCTURE" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\MCAL" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\MCAL\DIO" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\MCAL\EXT_INTERRUPT" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\MCAL\G_INTERRUPT" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\MCAL\MCU_POWER" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\MCAL\TIMER" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


