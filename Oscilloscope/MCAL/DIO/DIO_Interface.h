/*
 * DIO_Interface.h
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy "WAZEER"
 */

#ifndef __MCAL_DIO_DIO_INTERFACE_H__
#define __MCAL_DIO_DIO_INTERFACE_H__


#include "Data_Types.h"

/* Register width */
#define BITS_PER_REGISTER 	8U

/* ports & pins range */
#define MAX_PORTS 		4U
#define MAX_PINS 		32U
#define MIN_PORTS 		0U
#define MIN_PINS 		0U

/* Ports Name */
#define DIO_PORTA		0U
#define DIO_PORTB 		1U
#define DIO_PORTC 		2U
#define DIO_PORTD 		3U

/* Port A Pins Name */
#define DIO_PA0 	0U
#define DIO_PA1 	1U
#define DIO_PA2 	2U
#define DIO_PA3 	3U
#define DIO_PA4		4U
#define DIO_PA5 	5U
#define DIO_PA6 	6U
#define DIO_PA7 	7U
/* Port B Pins Name */
#define DIO_PB0		8U
#define DIO_PB1		9U
#define DIO_PB2		10U
#define DIO_PB3		11U
#define DIO_PB4		12U
#define DIO_PB5		13U
#define DIO_PB6		14U
#define DIO_PB7		15U
/* Port C Pins Name */
#define DIO_PC0		16U
#define DIO_PC1 	17U
#define DIO_PC2 	18U
#define DIO_PC3 	19U
#define DIO_PC4		20U
#define DIO_PC5 	21U
#define DIO_PC6 	22U
#define DIO_PC7 	23U
/* Port D Pins Name */
#define DIO_PD0		24U
#define DIO_PD1 	25U
#define DIO_PD2 	26U
#define DIO_PD3 	27U
#define DIO_PD4		28U
#define DIO_PD5 	29U
#define DIO_PD6 	30U
#define DIO_PD7 	31U

#define HIGH_PIN		0x01U
#define LOW_PIN  		0x00U
#define HIGH_PORT		0xFFU
#define LOW_PORT		0x00U

#define OUTPUT_PIN 		0x01U
#define INPUT_PIN 		0x00U
#define OUTPUT_PORT		0xFFU
#define INPUT_PORT		0x00U


//Set the direction of pin in port
extern uint8_t DIO_INIT_Pin(uint8_t au8_PinNumberCpy, uint8_t au8_DirectionCpy);
//Set port direction
extern uint8_t DIO_INIT_Port(uint8_t au8_PortNumberCpy,uint8_t au8_ValueCpy);

//Set the value of output pin in port
extern uint8_t DIO_Write_Pin(uint8_t au8_PinNumberCpy,uint8_t au8_ValueCpy);
//Set the output value of port
extern uint8_t DIO_Write_Port(uint8_t au8_PortNumberCpy,uint8_t au8_ValueCpy);

//Get the value of input pin in port
extern uint8_t DIO_Read_Pin(uint8_t au8_PinNumberCpy, uint8_t * pu8_PinValueCpy);
//Get the input value on port
extern uint8_t DIO_Read_Port(uint8_t au8_PortNumberCpy, uint8_t * pu8_PortValueCpy);

//Pullup pin in port
extern uint8_t DIO_Pullup_Pin(uint8_t au8_PinNumberCpy);
//Pullup port
extern uint8_t DIO_Pullup_Port(uint8_t au8_PortNumberCpy);

//Toggle pin in port
extern uint8_t DIO_Toggle_Pin(uint8_t au8_PortNumberCpy) ;
//Toggle port
extern uint8_t DIO_Toggle_Port(uint8_t au8_PortNumberCpy) ;


#endif /* __MCAL_DIO_DIO_INTERFACE_H__ */
