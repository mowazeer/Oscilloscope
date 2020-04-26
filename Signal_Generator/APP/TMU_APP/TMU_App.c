/*
 * TMU_App.c
 *
 *  Created on: Apr 21, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */


#include "TMU_App.h"


/***************************************************************************************/
/* brief!  Initialize used modules "included modules"                                  */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
void TMU_App_Init(void)
{
	/*
	*	Initializing the LEDS
	*/
	Init_LEDS();
	/*
	*	Initialize the TMU with a certain resolution
	*/
	TMU_Init(1000);
}

/***************************************************************************************/
/* brief!  Run our scenario                                                            */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
void TMU_App_Main(void)
{

	TMU_Start(LED1_Toggle , 250UL  , PERIODIC);
	TMU_Start(LED2_Toggle , 500UL  , PERIODIC);
	TMU_Start(LED3_Toggle , 1000UL , PERIODIC);
	TMU_Start(LED4_Toggle , 2000UL , ONE_SHOT);

	//TMU_Stop(LED1_Toggle);
	//TMU_Restart(LED1_Toggle);
	while (1)
	{
		TMU_Dispatcher();

		//CPU_Sleep();
	}
}
