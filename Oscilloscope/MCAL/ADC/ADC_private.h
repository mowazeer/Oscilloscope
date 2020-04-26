/*
 * ADC_private.h
 *
 *  Created on: Apr 18, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __MCAL_ADC_ADC_PRIVATE_H__
#define __MCAL_ADC_ADC_PRIVATE_H__


#define SFIOR	 *((volatile uint8_t*) 0x50U)
#define ADMUX	 *((volatile uint8_t*) 0x27U)
#define ADCSRA 	 *((volatile uint8_t*) 0x26U)
#define ADCH 	 *((volatile uint8_t*) 0x25U)
#define ADCL	 *((volatile uint8_t*) 0x24U)


#endif /* __MCAL_ADC_ADC_PRIVATE_H__ */
