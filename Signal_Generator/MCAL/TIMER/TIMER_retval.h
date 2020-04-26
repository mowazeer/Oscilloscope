/*
 * TIMER _retval.h
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __MCAL_TIMER_TIMER__RETVAL_H__
#define __MCAL_TIMER_TIMER__RETVAL_H__

#include "Retval.h"

/*
*	Error macros
*/
#define TIMER_ERROR_BASE_CODE       (error_t)(20U)
#define E_CHANNEL 					(error_t)(TIMER_ERROR_BASE_CODE + 1U )  /* channel error */
#define E_PSC 						(error_t)(TIMER_ERROR_BASE_CODE + 2U )  /* prescaler error  */
#define E_TIMER_MODE 				(error_t)(TIMER_ERROR_BASE_CODE + 3U )  /* Timer or counter mode error  */
#define E_INTERRUPT_MODE  			(error_t)(TIMER_ERROR_BASE_CODE + 4U )  /* Interrupt or Polling mode error   */
#define E_PTR_IS_NULL 				(error_t)(TIMER_ERROR_BASE_CODE + 5U )  /* NULL pointer error when using it */
#define E_TICKS 					(error_t)(TIMER_ERROR_BASE_CODE + 6U )  /* Ticks error "number of Ticks more than the max allowed" */


#endif /* __MCAL_TIMER_TIMER__RETVAL_H__ */
