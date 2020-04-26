/*
 * DIO_private.h
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy "WAZEER"
 */

#ifndef __MCAL_DIO_DIO_PRIVATE_H__
#define __MCAL_DIO_DIO_PRIVATE_H__


#include "Data_Types.h"

#define PORTA	 *((volatile uint8_t*) 0x3BU)
#define DDRA 	 *((volatile uint8_t*) 0x3AU)
#define PINA 	 *((volatile uint8_t*) 0x39U)

#define PORTB	 *((volatile uint8_t*) 0x38U)
#define DDRB 	 *((volatile uint8_t*) 0x37U)
#define PINB 	 *((volatile uint8_t*) 0x36U)

#define PORTC	 *((volatile uint8_t*) 0x35U)
#define DDRC	 *((volatile uint8_t*) 0x34U)
#define PINC	 *((volatile uint8_t*) 0x33U)

#define PORTD	 *((volatile uint8_t*) 0x32U)
#define DDRD  	 *((volatile uint8_t*) 0x31U)
#define PIND 	 *((volatile uint8_t*) 0x30U)


#endif /* __MCAL_DIO_DIO_PRIVATE_H__ */
