/*
 * MCU_Power.h
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __MCAL_MCU_POWER_MCU_POWER_H__
#define __MCAL_MCU_POWER_MCU_POWER_H__


#include "Data_Types.h"

/*
* Definitions bits of "MCUCR" Register that contains control bits for power management.
*/
#define MCUCR 		*((volatile uint8_t*) 0x55U)

#define SM0 	4U
#define SM1 	5U
#define SM2 	6U
#define SE  	7U


 /* CPU Sleep Modes */
#define CPU_SLEEP_MASK 				(0X70U)
#define CPU_IDLE					(0U << 4U)
#define CPU_ADC_NOISE_REDUCTION     (1U << 4U)
#define CPU_POWER_DOWN				(2U << 4U)
#define CPU_POWER_SAVE    			(3U << 4U)
#define CPU_RESERVED_1				(4U << 4U)
#define CPU_RESERVED_2     			(5U << 4U)
/* Note: 1. Standby mode and Extended Standby mode are only available
 * with external crystals or resonators.
 */
#define CPU_STANDBY					(6U << 4U)
#define CPU_EXTENDED_STANDBY     	(7U << 4U)


/***************************************************************************************/
/* brief!  function that Enable MCU sleep mode    								       */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
extern void Enable_CPU_Sleep(void);

/***************************************************************************************/
/* brief!  function that Disable MCU sleep mode    								       */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
extern void Disable_CPU_Sleep(void);

/***************************************************************************************/
/* brief!  function that make the MCU enter the chosen sleep mode 					   */
/* param!  u8 (i/p)chosen sleep mode                                                   */
/* return! void                                                                        */
/***************************************************************************************/
extern void CPU_Sleep(uint8_t au8_Sleep_Mode);


#endif /* __MCAL_MCU_POWER_MCU_POWER_H__ */
