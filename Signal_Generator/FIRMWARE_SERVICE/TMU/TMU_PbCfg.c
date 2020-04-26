/*
 * TMU_PbCfg.c
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy "Wazeer"
 */

#include "TMU_PbCfg.h"

/*
* NOTE: Changing any of these configuration will automatically changes the configuration of TMU.
* NOTE: Do not forget to change the PRESCALE_VALUE in TMU_cfg.h
* NOTE: In case of changing the timer channel you have to change the ISR vector in TMU.c
* NOTE: Timer1 is the default timer channel
*/

/*
 * used Timer configuration
 */
Timer_cfg_s TMU_Config = { TIMER1, T1_PSC_1024, TIMER_MODE, INTERRUPT };
