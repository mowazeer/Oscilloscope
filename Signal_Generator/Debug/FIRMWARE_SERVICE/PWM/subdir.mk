################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FIRMWARE_SERVICE/PWM/PWM.c \
../FIRMWARE_SERVICE/PWM/PWM_PbCfg.c 

OBJS += \
./FIRMWARE_SERVICE/PWM/PWM.o \
./FIRMWARE_SERVICE/PWM/PWM_PbCfg.o 

C_DEPS += \
./FIRMWARE_SERVICE/PWM/PWM.d \
./FIRMWARE_SERVICE/PWM/PWM_PbCfg.d 


# Each subdirectory must supply rules for building sources it contributes
FIRMWARE_SERVICE/PWM/%.o: ../FIRMWARE_SERVICE/PWM/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\APP" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\APP\PWM_APP" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\APP\SOS_APP" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\APP\TMU_APP" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\ECUAL" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\ECUAL\LEDs" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\INFRA_STRUCTURE" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\MCAL" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\MCAL\DIO" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\MCAL\EXT_INTERRUPT" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\MCAL\G_INTERRUPT" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\MCAL\MCU_POWER" -I"E:\Embedded\IMT\AVR_32_workspace\Signal_Generator\MCAL\TIMER" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


