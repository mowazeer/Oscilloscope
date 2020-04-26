/*
 * EXT_INTE_Private.h
 *
 *  Created on: Jan 19, 2020
 *      Author: MO._.Hamdy
 */

#ifndef __MCAL_EXT_INTERRUPT_EXT_INTE_PRIVATE_H__
#define __MCAL_EXT_INTERRUPT_EXT_INTE_PRIVATE_H__


#include "Data_Types.h"

/*
*	Interrupts registers
*/
#define MCUCR   ( *((volatile uint8_t *) (0x55) ) )
#define MCUCSR  ( *((volatile uint8_t *) (0x54) ) )

#define GICR    ( *((volatile uint8_t *) (0x5B) ) )
#define GIFR    ( *((volatile uint8_t *) (0x5A) ) )



#endif /* __MCAL_EXT_INTERRUPT_EXT_INTE_PRIVATE_H__ */
