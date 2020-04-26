/*
 * SOS_App.c
 *
 *  Created on: Apr 21, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */


#include "SOS_App.h"


/***************************************************************************************/
/* brief!  Initialize used modules "included modules"                                  */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
void SOS_App_Init(void)
{
	/*
	*	Initializing the LEDS
	*/
	Init_LEDS();
	/*
	*	Initialize the SOS with a certain resolution
	*/
	SOS_Init(SOS_RESOLUTION_IN_MICRO);
}

/***************************************************************************************/
/* brief!  Run our scenario                                                            */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
void SOS_App_Main(void)
{

	SOS_CreatTask(LED1_Toggle , 250UL  , 0U , PERIODIC);
	SOS_CreatTask(LED2_Toggle , 500UL  , 1U , PERIODIC);
	SOS_CreatTask(LED3_Toggle , 1000UL , 2U , PERIODIC);
	SOS_CreatTask(LED4_Toggle , 2000UL , 3U , PERIODIC);

	//SOS_DeleteTask(LED4_Toggle);

	SOS_Run();

	//CPU_Sleep();
}
