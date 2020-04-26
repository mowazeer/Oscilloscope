/*
 * MCU_Power.c
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy "Wazeer"
 */


#include "Macros.h"
#include "MCU_Power.h"



/***************************************************************************************/
/* brief!  function that Enable MCU sleep mode    								       */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
void Enable_CPU_Sleep(void)
{
	/* Enable the sleep mode */
	SET_BIT(MCUCR, SE);
}

/***************************************************************************************/
/* brief!  function that Disable MCU sleep mode                    					   */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
void Disable_CPU_Sleep(void)
{
	/* Disable the sleep mode */
	CLEAR_BIT(MCUCR, SE);
}

/***************************************************************************************/
/* brief!  function that make the MCU enter the chosen sleep mode 					   */
/* param!  u8 (i/p)chosen sleep mode                                                   */
/* return! void                                                                        */
/***************************************************************************************/
void CPU_Sleep(uint8_t au8_Sleep_Mode)
{
	if((CPU_IDLE <= au8_Sleep_Mode) && (CPU_EXTENDED_STANDBY >= au8_Sleep_Mode))
	{
		CLEAR_MASK(MCUCR, CPU_SLEEP_MASK);
		SET_MASK(MCUCR, au8_Sleep_Mode);
	}
}
