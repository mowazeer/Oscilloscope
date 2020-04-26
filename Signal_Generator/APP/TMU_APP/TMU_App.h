/*
 * TMU_App.h
 *
 *  Created on: Apr 21, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __APP_TMU_APP_TMU_APP_H__
#define __APP_TMU_APP_TMU_APP_H__


/*
*	Header files inclusions
*/
#include <FIRMWARE_SERVICE/TMU/TMU.h>
#include "DIO_Interface.h"
#include "LEDS.h"
#include "MCU_Power.h"

/***************************************************************************************/
/* brief!  Initialize used modules "included modules"                                  */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
extern void TMU_App_Init(void);

/***************************************************************************************/
/* brief!  Initialize The output pins for LEDS                                         */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
extern void TMU_App_Main(void);


#endif /* __APP_TMU_APP_TMU_APP_H__ */
