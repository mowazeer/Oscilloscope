/*
 * TIMER_Private.h
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __MCAL_TIMER_TIMER_PRIVATE_H__
#define __MCAL_TIMER_TIMER_PRIVATE_H__

#include "Data_Types.h"

/*
*	Timer registers
*/
#define TIMSK  ( *((volatile uint8_t *) (0x59) ) )
#define TIFR   ( *((volatile uint8_t *) (0x58) ) )

/*
*	Timer 0 registers
*/
#define TCNT0   ( *((volatile uint8_t *) (0x52) ) )
#define TCCR0   ( *((volatile uint8_t *) (0x53) ) )
#define OCR0    ( *((volatile uint8_t *) (0x5C) ) )

/*
*	Timer 1 registers
*/
#define TCCR1A  ( *((volatile uint8_t *) (0x4F) ) )
#define TCCR1B  ( *((volatile uint8_t *) (0x4E) ) )

#define TCNT1H  ( *((volatile uint8_t *) (0x4D) ) )
#define TCNT1L  ( *((volatile uint8_t *) (0x4C) ) )
#define TCNT1   ( *((volatile uint16_t *) (0x4C) ) )

#define OCR1AH ( *((volatile uint8_t *) (0x4B) ) )
#define OCR1AL ( *((volatile uint8_t *) (0x4A) ) )
#define OCR1BH ( *((volatile uint8_t *) (0x49) ) )
#define OCR1BL ( *((volatile uint8_t *) (0x48) ) )
#define OCR1A  ( *((volatile uint16_t *) (0x4A) ) )
#define OCR1B  ( *((volatile uint16_t *) (0x48) ) )

#define ICR1H  ( *((volatile uint8_t *) (0x47) ) )
#define ICR1L  ( *((volatile uint8_t *) (0x46) ) )


/*
*	Timer 2 registers
*/
#define TCCR2  ( *((volatile uint8_t *) (0x45) ) )
#define TCNT2  ( *((volatile uint8_t *) (0x44) ) )
#define OCR2   ( *((volatile uint8_t *) (0x43) ) )
#define ASSR   ( *((volatile uint8_t *) (0x42) ) )


#endif /* __MCAL_TIMER_TIMER_PRIVATE_H__ */
