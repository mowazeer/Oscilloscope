/*
 * Osc.h
 *
 *  Created on: Apr 19, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __APP_OSC_APP_OSC_H__
#define __APP_OSC_APP_OSC_H__

#include "Data_Types.h"
#include "ADC.h"


#define SAMPLING_TIME 		4U	// SAMPLE TIME FOR 62.5 KHZ SAMPLE RATE //todo
#define NUM_SAMPLE 			800U	// NUMBER OF SAMPLE //todo


 /* Signal "ADC" Channel */
#define SIGNAL_CH0     		ADC_CH0
#define SIGNAL_CH1			ADC_CH1
#define SIGNAL_CH2    		ADC_CH2
#define SIGNAL_CH3			ADC_CH3
#define SIGNAL_CH4     		ADC_CH4
#define SIGNAL_CH5			ADC_CH5
#define SELECT_TIME_DIV		ADC_CH6
#define SELECT_SIGNAL_CH    ADC_CH7


/***************************************************************************************/
/* brief!  Function that Initialize the Oscilloscope display and the hardware he needed*/
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
extern void Osc_Display_Init(void);

/***************************************************************************************/
/* brief!  Function that have the Oscilloscope Scenario to Work						   */
/* param!  void																	       */
/* return! void                                                                        */
/***************************************************************************************/
extern void Osc_Main(void);


#endif /* __APP_OSC_APP_OSC_H__ */
