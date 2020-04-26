/*
 * PWM_PbCfg.c
 *
 *  Created on: Apr 20, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */


#include "PWM_PbCfg.h"

/*
* NOTE: Changing any of these configuration will automatically changes the configuration of PWM.
* NOTE: Do not forget to change the PRESCALE_VALUE in PWM_cfg.h
* NOTE: In case of changing the timer channel you have to change the ISR vector in Timer.c
* NOTE: Timer1 is the default timer channel
*/

/*
 * used Timer configuration
 */
Timer_cfg_s PWM_Config = { TIMER1, T1_PSC_1024, TIMER_MODE, INTERRUPT };
