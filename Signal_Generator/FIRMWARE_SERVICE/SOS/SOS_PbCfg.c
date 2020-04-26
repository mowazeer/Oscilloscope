/*
 * SOS_PbCfg.c
 *
 *  Created on: Jan 7, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */


#include "SOS_PbCfg.h"

/*
* NOTE: Changing any of these configuration will automatically changes the configuration of SOS.
* NOTE: Do not forget to change the PRESCALE_VALUE in SOS_cfg.h
* NOTE: In case of changing the timer channel you have to change the ISR vector in SOS.c
* NOTE: Timer1 is the default timer channel
*/

/*
 * used Timer configuration
 */
Timer_cfg_s SOS_Config = { TIMER1, T1_PSC_1024, TIMER_MODE, INTERRUPT };
