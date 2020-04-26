/*
 * Interrupt.h
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy
 */

#ifndef __MCAL_G_INTERRUPT_INTERRUPT_H__
#define __MCAL_G_INTERRUPT_INTERRUPT_H__


#include "Data_Types.h"
#include "avr/interrupt.h"

/*
* Definitions bits of "SREG" Register that contains Status Register.
*/
#define SREG     *((volatile uint8_t*) 0x5FU)

#define GI 		7U


/***************************************************************************************/
/* brief!  function that enable the global interrupt                                   */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
extern void Enable_GlobalInterrupt(void);

/***************************************************************************************/
/* brief!  function that disable the global interrupt                                  */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
extern void Disable_GlobalInterrupt(void);


#endif /* __MCAL_G_INTERRUPT_INTERRUPT_H__ */
