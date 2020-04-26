/*
 * Main.c
 *
 *  Created on: Apr 20, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */

//#include "TMU_App.h"
//#include "SOS_App.h"
#include "PWM_App.h"


int main(void)
{

	/*
	TMU_App_Init();
	TMU_App_Main();
	*/

	/*
	SOS_App_Init();
	SOS_App_Main();
	*/


	PWM_App_Init();
	PWM_App_Main();


	while(1)
	{

	}
return 0;
}
