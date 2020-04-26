/*
 * Interrupt.c
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy
 */


#include "Macros.h"
#include "Interrupt.h"


/***************************************************************************************/
/* brief!  function that enable the global interrupt                                   */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
void Enable_GlobalInterrupt(void)
{
	/*
	*	Enable global interrupt
	*/
	SET_BIT(SREG, GI);
}

/***************************************************************************************/
/* brief!  function that disable the global interrupt                                  */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
void Disable_GlobalInterrupt(void)
{
	/*
	*	Disable global interrupt
	*/
	CLEAR_BIT(SREG, GI);
}
