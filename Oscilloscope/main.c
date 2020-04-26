/*
 * main.c
 *
 *  Created on: Apr 18, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */
#include "Osc.h"

int main(void)
{

	Osc_Display_Init();

	while(1)
	{
		Osc_Main();
	}

	return 0 ;
}
