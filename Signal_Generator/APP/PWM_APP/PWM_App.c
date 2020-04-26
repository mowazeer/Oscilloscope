/*
 * Pwm_App.c
 *
 *  Created on: Apr 21, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */


#include "PWM_App.h"


/***************************************************************************************/
/* brief!  Initialize used modules "included modules"                                  */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
void PWM_App_Init(void)
{
	/*
	*	Initialize the PWM with a certain resolution
	*/
	PWM_Init(1000);

	PWM_Channel_Init(0U, DIO_PB4, 50, 100);
	PWM_Channel_Init(1U, DIO_PB5, 70, 100);
	PWM_Channel_Init(2U, DIO_PB6, 50, 50);
	PWM_Channel_Init(3U, DIO_PB7, 30, 50);

}

/***************************************************************************************/
/* brief!  Run our scenario                                                            */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
void PWM_App_Main(void)
{

	PWM_Channel_Start(0U);
	PWM_Channel_Start(1U);
	PWM_Channel_Start(2U);
	PWM_Channel_Start(3U);

	while (1)
	{

		//CPU_Sleep();
	}
}
