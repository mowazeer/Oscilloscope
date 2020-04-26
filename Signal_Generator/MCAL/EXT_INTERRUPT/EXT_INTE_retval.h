/*
 * EXT_INTE_retval.h
 *
 *  Created on: Jan 19, 2020
 *      Author: MO._.Hamdy
 */

#ifndef __MCAL_EXT_INTEERRUPT_EXT_INTE_RETVAL_H__
#define __MCAL_EXT_INTEERRUPT_EXT_INTE_RETVAL_H__


#include "Retval.h"

/*
*	Error macros
*/
#define EXT_INTE_ERROR_BASE_CODE    (error_t)(40U)
#define E_INTE_REQUEST 				(error_t)(EXT_INTE_ERROR_BASE_CODE + 1U )  /* channel error */
#define E_INTE0_SENSE_CONTROL 		(error_t)(EXT_INTE_ERROR_BASE_CODE + 2U )  /* prescaler error  */
#define E_INTE1_SENSE_CONTROL 		(error_t)(EXT_INTE_ERROR_BASE_CODE + 3U )  /* prescaler error  */
#define E_INTE2_SENSE_CONTROL 		(error_t)(EXT_INTE_ERROR_BASE_CODE + 4U )  /* prescaler error  */
#define E_INTE_NOT_INTIALIZED 		(error_t)(EXT_INTE_ERROR_BASE_CODE + 5U )

#endif /* __MCAL_EXT_INTEERRUPT_EXT_INTE_RETVAL_H__ */
