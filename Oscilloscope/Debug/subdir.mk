################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c 

OBJS += \
./main.o 

C_DEPS += \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\Embedded\IMT\AVR_32_workspace\Oscilloscope" -I"E:\Embedded\IMT\AVR_32_workspace\Oscilloscope\APP" -I"E:\Embedded\IMT\AVR_32_workspace\Oscilloscope\APP\Osc_App" -I"E:\Embedded\IMT\AVR_32_workspace\Oscilloscope\ECUAL" -I"E:\Embedded\IMT\AVR_32_workspace\Oscilloscope\ECUAL\LCD_TFT_ili9486" -I"E:\Embedded\IMT\AVR_32_workspace\Oscilloscope\INFRA_STRUCTURE" -I"E:\Embedded\IMT\AVR_32_workspace\Oscilloscope\MCAL" -I"E:\Embedded\IMT\AVR_32_workspace\Oscilloscope\MCAL\ADC" -I"E:\Embedded\IMT\AVR_32_workspace\Oscilloscope\MCAL\DIO" -I"E:\Embedded\IMT\AVR_32_workspace\Oscilloscope\MCAL\G_INTERRUPT" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


