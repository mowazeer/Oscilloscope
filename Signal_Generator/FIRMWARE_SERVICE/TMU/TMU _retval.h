/*
 * TMU _retval.h
 *
 *  Created on: Dec 22, 2019
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __TMU_RETVAL_H__
#define __TMU_RETVAL_H__

#include "Retval.h"

/*
 *	Error macros
 */
#define TMU_ERROR_BASE_CODE       	(error_t)(100U)
#define E_PERIODICITY 				(error_t)(TMU_ERROR_BASE_CODE + 1U )
#define E_READY 					(error_t)(TMU_ERROR_BASE_CODE + 2U )
#define E_FIRST_EXECUTION_INDIC 	(error_t)(TMU_ERROR_BASE_CODE + 3U )
#define E_Ok_TOGO 					(error_t)(TMU_ERROR_BASE_CODE + 4U )
#define E_RESOLUTION				(error_t)(TMU_ERROR_BASE_CODE + 5U )
#define E_EVENT 					(error_t)(TMU_ERROR_BASE_CODE + 6U )
#define E_NUMBER_OF_EVENTS 			(error_t)(TMU_ERROR_BASE_CODE + 7U )
#define E_TMU_INTIALIZED 			(error_t)(TMU_ERROR_BASE_CODE + 8U )
#define E_TMU_NOT_INTIALIZED 		(error_t)(TMU_ERROR_BASE_CODE + 9U )

#endif /* __TMU_RETVAL_H__ */
