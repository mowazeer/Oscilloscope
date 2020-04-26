/*
 * ADC_PbCfg.c
 *
 *  Created on: Apr 19, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */


#include "ADC_PbCfg.h"

/*
 * NOTE: Changing any of these configuration will automatically changes the configuration of ADC.
 */

/*
 * used ADC configuration
 */
str_ADC_cfg_t ADC_Config = { ADC_CH0, ADC_INTERNAL_VCC, ADC_RIGHT_ADJUST, ADC_PSC_128, ADC_POLLING, ADC_MANUAL_TRIGGER };
