/*
 * Osc.c
 *
 *  Created on: Apr 19, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */

#include "Osc.h"
#include "TFT_Interface.h"
#include "ADC.h"
#include "ADC_PbCfg.h"

/*
 *	Static variable that will hold the ISR counter
 */
static uint16_t gu8_ISR_Count = INITIAL;

/*
 *	Static global Array that will hold the (ADC) Digital Values "Array that hold the signal samples"
 */
static uint16_t gau16_Volt[NUM_SAMPLE];


/***************************************************************************************/
/* brief!  what ISR handling                                                           */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
static void ADC_CallBack(uint8_t au8_ADC_L, uint8_t au8_ADC_H)
{
	/* Handling ADC Right Adjust */
	gau16_Volt[gu8_ISR_Count++] = ((uint16_t) au8_ADC_L) | ((uint16_t)(au8_ADC_H << 8U));

	/* Handling ADC Left Adjust */
	//gau16_Volt[index++] = ((uint16_t)(au8_ADC_L >> 6U)) | ((uint16_t)(au8_ADC_H << 2U));

	// initiate the array index when it reach to the last index
	if(NUM_SAMPLE == gu8_ISR_Count)
	{
		gu8_ISR_Count = INITIAL;
	}

}

/***************************************************************************************/
/* brief!  static function that Calculate the Maximum volt                             */
/* param!  (i/p) array of u16 that hold the signal samples                             */
/* param!  (o/p) pu16 that hold the Maximum volt                                        */
/* param!  (o/p) pu16 that hold the Maximum volt index                                  */
/* return! void                                                                        */
/***************************************************************************************/
static void Max_V (uint16_t *pu16_Arr, uint16_t *u16_Max_Val, uint16_t *u16_Max_Loc)
{
	/* variable that hold array index */
	uint16_t  u16_index = INITIAL;

	*u16_Max_Val = pu16_Arr[0U]; /* init. the u16_Max_Val with the first array value */
	*u16_Max_Loc = INITIAL; 	 /* init. the u16_Max_Loc with the first array index */

	for(u16_index = 1U; u16_index < NUM_SAMPLE; u16_index++)
	{
		/* Compare the array element until we reach to Maximum Volt */
		if(*u16_Max_Val < pu16_Arr[u16_index])
		{
			*u16_Max_Val = pu16_Arr[u16_index];
			*u16_Max_Loc = u16_index;
		}
	}
}

/***************************************************************************************/
/* brief!  static function Calculate the Minimum volt                                  */
/* param!  (i/p) array of u16 that hold the signal samples                             */
/* param!  (o/p) pu16 that hold the Minimum volt                                        */
/* param!  (o/p) pu16 that hold the Minimum volt index                                  */
/* return! void                                                                        */
/***************************************************************************************/
static void Min_V(uint16_t *pu16_Arr, uint16_t *u16_Min_Val, uint16_t *u16_Min_Loc)
{
	/* variable that hold array index */
	uint16_t  u16_index = INITIAL;

	*u16_Min_Val = pu16_Arr[0U]; /* init. the u16_Min_Val with the first array value */
	*u16_Min_Loc = INITIAL; 	 /* init. the u16_Min_Loc with the first array index */

	for (u16_index = 1U; u16_index < NUM_SAMPLE; u16_index++)
	{
		/* Compare the array element until we reach to Minimum Volt */
		if (*u16_Min_Val > pu16_Arr[u16_index])
		{
			*u16_Min_Val = pu16_Arr[u16_index];
			*u16_Min_Loc = u16_index;
		}
	}
}

/***************************************************************************************/
/* brief!  static function Calculate the Signal Periodic Time                          */
/* param!  (i/p) array of u16 that hold the signal samples                             */
/* param!  (i/p) u16 that hold the signal Average volt                                 */
/* param!  (o/p) pointer to u32 that hold the signal Periodic Time                     */
/* return! void                                                                        */
/***************************************************************************************/
static void Signal_Time(uint16_t *pu16_Arr, uint16_t u16_Avg_V, uint32_t *pu32_PerTime)
{
	uint16_t u16_Snap_1 = INITIAL; /* variable that hold array index at the first snapshot */
	uint16_t u16_Snap_2 = INITIAL; /* variable that hold array index at the second snapshot  */
	uint8_t u8_Snap_N = INITIAL;   /* variable that hold the snapshot state condition */

	/* variable that hold array index */
	uint16_t u16_index = INITIAL ;

	for(u16_index = INITIAL; u16_index < NUM_SAMPLE; u16_index++)
	{
		if((pu16_Arr[u16_index] < u16_Avg_V) && (pu16_Arr[u16_index +1U] > u16_Avg_V))
		{
			if(INITIAL == u8_Snap_N)
			{
				u16_Snap_1 = u16_index ;
				u8_Snap_N = 1U;
			}
			else
			{
				u16_Snap_2 = u16_index ;
				u8_Snap_N = INITIAL;

				*pu32_PerTime = (uint32_t)(u16_Snap_2 - u16_Snap_1) / SAMPLING_TIME;

				break;
			}
		}
		else
		{
			*pu32_PerTime = INITIAL;
		}
	}
}

/***************************************************************************************/
/* brief!  static function that Scale the input value to another scale 				   */
/* param!  (i/p) s32 that hold the input value 			                               */
/* param!  (i/p) s32 that hold the Minimum value input			                       */
/* param!  (i/p) s32 that hold the Maximum value input			                       */
/* param!  (i/p) s32 that hold the Minimum value output			                       */
/* param!  (i/p) s32 that hold the Maximum value output			                       */
/* return! (i/p) s32 that hold the output value                                        */
/***************************************************************************************/
static sint32_t ReScale(sint32_t value, sint32_t in_min, sint32_t in_max, sint32_t out_min, sint32_t out_max)
{
	return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/***************************************************************************************/
/* brief!  static function that print Grid on the Screen 					           */
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
static void Osc_Display_Grid(void)
{
	uint16_t u16_Row = INITIAL; 	/* variable that hold Horizontal cursor position "X-Axis" */
	uint16_t u16_Col = INITIAL; 	/* variable that hold Vertical cursor position "Y-Axis" */

	/* Fill the Grid Rectangular with BLAK at the first */
	TFT_Fill_Rect(17U, 49U, 363U, 222U, ILI9486_BLACK);

	/* Draw the Horizontal Lines */
	for(u16_Row = 60; u16_Row <= 260; u16_Row += 20)
	{
		TFT_Draw_HLine(17, u16_Row, 363, ILI9486_OLIVE);
	}

	/* Draw the Vertical Lines */
	for(u16_Col = 20; u16_Col <= 360; u16_Col += 20)
	{
		TFT_Draw_VLine(u16_Col, 49, 223, ILI9486_OLIVE);
	}
}

/***************************************************************************************/
/* brief!  Function that Initialize the Oscilloscope display and the hardware he needed*/
/* param!  void                            			                                   */
/* return! void                                                                        */
/***************************************************************************************/
void Osc_Display_Init(void)
{

	ADC_Init(&ADC_Config); 			/* Initialize ADC Module */
	ADC_SetCallBack(ADC_CallBack);  /* Set ADC function that will run inside ADC the ISR if we choice the ADC INTERRUPT Mode */

	TFT_Init(); 					/* Initialize TFT screen */


	TFT_Fill_Screen(ILI9486_BLACK); /* FILL SCREEN WITH BLACK */

	/* Draw some green Lines "Screen Main Lines" */
	TFT_Draw_HLine(INITIAL, 48, 380, ILI9486_GREEN);
	TFT_Draw_HLine(INITIAL, 272, 380, ILI9486_GREEN);
	TFT_Draw_VLine(380, INITIAL, 320, ILI9486_GREEN);

	/* Display the string "Oscilloscope" the name on our project*/
	TFT_SetCursor(75U, 8U);
	TFT_SetTextColor(ILI9486_GREENYELLOW,ILI9486_BLACK);
	TFT_Print_String((uint8_t *)"Oscilloscope CH_", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	/* Display the string "TimDiv" */
	TFT_SetCursor(388, 2);
	TFT_SetTextColor(ILI9486_GREEN,ILI9486_BLACK);
	TFT_Print_String((uint8_t *)"TimDiv", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	/* Display the string "Freq =" */
	TFT_SetCursor(2, 285);
	TFT_SetTextColor(ILI9486_GREEN, ILI9486_BLACK);
	TFT_Print_String((uint8_t *)"Freq =", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	/* Display the string "T =" */
	TFT_SetCursor(195, 285);
	TFT_SetTextColor(ILI9486_GREEN, ILI9486_BLACK);
	TFT_Print_String((uint8_t *)"T =", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	/* Display the string "Avg_V" */
	TFT_SetCursor(388, 85);
	TFT_SetTextColor(ILI9486_GREEN, ILI9486_BLACK);
	TFT_Print_String((uint8_t *)"Avg_V", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	/* Display the string "Max_V" */
	TFT_SetCursor(388, 165);
	TFT_SetTextColor(ILI9486_GREEN, ILI9486_BLACK);
	TFT_Print_String((uint8_t *)"Max_V", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	/* Display the string "Max_V" */
	TFT_SetCursor(388, 245);
	TFT_SetTextColor(ILI9486_GREEN, ILI9486_BLACK);
	TFT_Print_String((uint8_t *)"Min_V", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	/* Write and display the scale of the Signal Amplitude  */
	TFT_SetCursor(INITIAL, 250);
	TFT_SetTextColor(ILI9486_RED, ILI9486_BLACK);
	TFT_Print_String((uint8_t *)"0", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	TFT_SetCursor(INITIAL, 210);
	TFT_Print_String((uint8_t *)"1", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	TFT_SetCursor(INITIAL, 170);
	TFT_Print_String((uint8_t *)"2", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	TFT_SetCursor(INITIAL, 130);
	TFT_Print_String((uint8_t *)"3", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	TFT_SetCursor(INITIAL, 90);
	TFT_Print_String((uint8_t *)"4", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	TFT_SetCursor(INITIAL, 50);
	TFT_Print_String((uint8_t *)"5", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	/* Display Oscilloscope Grid */
	Osc_Display_Grid();
}

/***************************************************************************************/
/* brief!  Function that have the Oscilloscope Scenario to Work						   */
/* param!  (i/p) u8 that used to choice which signal we will sample and display        */
/* return! void                                                                        */
/***************************************************************************************/
void Osc_Main(void)
{
	uint16_t u16_Channel_Num = SIGNAL_CH0;	/* variable that will hold the Chosen Channel Number */

	uint16_t u16_Max_V = INITIAL;    /* variable that will hold the Maximum Signal Volt value */
	uint16_t u16_Min_V = INITIAL;    /* variable that will hold the Minimum Signal Volt value */
	uint16_t u16_Avg_V = INITIAL;	 /* variable that will hold the Average Signal Volt value */
	uint16_t u16_Index = INITIAL;    /* variable that will hold the Array Index */
	uint16_t u16_TimeDiv = 1U;		 /* variable that will hold the Time Division value */

	uint16_t u16_X = INITIAL; 		/* variable that will hold the Cursor X-Axis Position */
	uint32_t u32_PerTime = INITIAL; /* variable that will hold the Signal Periodic Time */

	uint16_t u16_Max_V_Loc = INITIAL; /* variable that will hold the Maximum volt Index "for future use" */
	uint16_t u16_Min_V_Loc = INITIAL; /* variable that will hold the Minimum volt Index "for future use" */

	ADC_Change_Channel(SELECT_SIGNAL_CH);	/* Change ADC Channel */
	ADC_Start_Conversion(); 				/* Start the First ADC Conversion */
	ADC_Read(&u16_Channel_Num);				/* Read ADC Digital Value */
	u16_Channel_Num = ReScale(u16_Channel_Num, INITIAL, 1024U, 0U, 6U);

	/* Display the "Channel Number" */
	TFT_SetCursor(300U, 8U);
	TFT_Fill_Rect(300U, 8U, 20U, 20U, ILI9486_BLACK);
	TFT_SetTextColor(ILI9486_GREENYELLOW,ILI9486_BLACK);
	TFT_Print_Number(u16_Channel_Num, TFT_CHAR_14_24, 1U);


	ADC_Change_Channel(SELECT_TIME_DIV);	/* Change ADC Channel */
	ADC_Start_Conversion(); 				/* Start the First ADC Conversion */
	ADC_Read(&u16_TimeDiv);					/* Read ADC Digital Value */
	u16_TimeDiv = ReScale(u16_TimeDiv, INITIAL, 1024U, 1U, 5U);

	/* Display Time per division */
	TFT_SetCursor(388U, 32U);
	TFT_Fill_Rect(388U, 32U, 20U, 20U, ILI9486_BLACK);
	TFT_SetTextColor(ILI9486_BLUE, ILI9486_BLACK);
	TFT_Print_Number(u16_TimeDiv, TFT_CHAR_14_24, 1U);
	TFT_SetTextColor(ILI9486_PURPLE, ILI9486_BLACK);
	TFT_Print_String((uint8_t *)" ms", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	/* Read the Signal Samples from the ADC Channel_1*/
	ADC_Change_Channel(u16_Channel_Num);	/* Change ADC Channel */
	for(u16_Index = INITIAL; u16_Index < NUM_SAMPLE ; u16_Index++)
	{
		ADC_Start_Conversion(); 			/* Start the First ADC Conversion */
		ADC_Read(&gau16_Volt[u16_Index]);	/* Read ADC Digital Value */
	}

	/* Convert the Signal Samples from Digital Value to Analog Value */
	for(u16_Index = INITIAL ; u16_Index < NUM_SAMPLE ; u16_Index++)
	{
		gau16_Volt[u16_Index] = ReScale(gau16_Volt[u16_Index], INITIAL, 1024U, INITIAL, 5005U);
	}

	Max_V(gau16_Volt, &u16_Max_V, &u16_Max_V_Loc); 		/* Calculate Maximum volt */
	Min_V(gau16_Volt, &u16_Min_V, &u16_Min_V_Loc);		/* Calculate Minimum volt */
	u16_Avg_V = (u16_Max_V + u16_Min_V) / 2U ; 			/* Calculate Average Volt */
	Signal_Time(gau16_Volt, u16_Avg_V, &u32_PerTime);	/* Calculate periodic Time */

	/* Scale the Signal to Fit the Screen Oscilloscope "Y AXIS" Grid */
	for(u16_Index = INITIAL ; u16_Index < NUM_SAMPLE  ; u16_Index++)
	{
		gau16_Volt[u16_Index] = ReScale(gau16_Volt[u16_Index], INITIAL, 5000U, 260U, 60U);
	}


	/* Scale the Signal to Fit the Screen Oscilloscope "X AXIS" Grid and Draw the Signal */
	for(u16_Index = 1U ; u16_Index < NUM_SAMPLE ; u16_Index++)
	{
		u16_X = ReScale(u16_Index, INITIAL, 799U, 22U, 390U);

		if(u16_X * u16_TimeDiv > 379U)
		{
			break;
		}
		/* Draw the signal on the Screen */
		TFT_Draw_CLine(((u16_X -1U)*u16_TimeDiv), gau16_Volt[u16_Index -1U], (u16_X*u16_TimeDiv), gau16_Volt[u16_Index], ILI9486_RED);
		_delay_ms(5);
	}


	/* CLEAR SCREEN BY REDRAW SIGNAL IN BLACK */
/*
	u16_X = INITIAL ;
	for(u16_Index = 1U ; u16_Index < NUM_SAMPLE ; u16_Index++)
	{
		u16_X = ReScale(u16_Index, INITIAL, 799U, 22U, 390U);

		if(u16_X * u8_TimeDiv > 379U)
		{
			break;
		}
		TFT_Draw_CLine(((u16_X -1U)*u8_TimeDiv), gau16_Volt[u16_Index -1U], (u16_X*u8_TimeDiv), gau16_Volt[u16_Index], ILI9486_BLACK);
	}
*/

	/* Display Signal Frequency */
	TFT_SetCursor(95U, 285U);
	TFT_Fill_Rect(95U, 285U, 100U, 20U, ILI9486_BLACK);
	TFT_SetTextColor(ILI9486_BLUE, ILI9486_BLACK);
	if(INITIAL != u32_PerTime)
	{
		TFT_Print_Number((1000U/u32_PerTime)+1U, TFT_CHAR_14_24, 1U);
	}
	else
	{
		TFT_Print_Number(INITIAL, TFT_CHAR_14_24, 1U);
	}
	TFT_SetTextColor(ILI9486_PURPLE, ILI9486_BLACK);
	TFT_Print_String((uint8_t *)" HZ", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	/* Display Periodic Time */
	TFT_SetCursor(250U, 285U);
	TFT_Fill_Rect(250U, 285U, 100U, 20U, ILI9486_BLACK);
	TFT_SetTextColor(ILI9486_BLUE, ILI9486_BLACK);
	TFT_Print_Number(u32_PerTime, TFT_CHAR_14_24, 1U);
	TFT_SetTextColor(ILI9486_PURPLE, ILI9486_BLACK);
	TFT_Print_String((uint8_t *)(uint8_t *)" ms", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	/* Display Average Volt */
	TFT_SetCursor(388U, 115U);
	TFT_Fill_Rect(388U, 115U, 100U, 20U, ILI9486_BLACK);
	TFT_SetTextColor(ILI9486_BLUE, ILI9486_BLACK);
	TFT_Print_Number(u16_Avg_V, TFT_CHAR_14_24, 1U);
	TFT_SetTextColor(ILI9486_PURPLE,ILI9486_BLACK);
	TFT_Print_String((uint8_t *)"mV", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	/* Display Maximum Volt */
	TFT_SetCursor(388U, 195U);
	TFT_Fill_Rect(388U, 195U, 100U, 20U, ILI9486_BLACK);
	TFT_SetTextColor(ILI9486_BLUE, ILI9486_BLACK);
	TFT_Print_Number(u16_Max_V, TFT_CHAR_14_24, 1U);
	TFT_SetTextColor(ILI9486_PURPLE, ILI9486_BLACK);
	TFT_Print_String((uint8_t *)"mV", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	/* Display Minimum Volt */
	TFT_SetCursor(388U, 275U);
	TFT_Fill_Rect(388U, 275U, 100U, 20U, ILI9486_BLACK);
	TFT_SetTextColor(ILI9486_BLUE, ILI9486_BLACK);
	TFT_Print_Number(u16_Min_V, TFT_CHAR_14_24, 1U);
	TFT_SetTextColor(ILI9486_PURPLE, ILI9486_BLACK);
	TFT_Print_String((uint8_t *)"mV", TFT_CHAR_14_24, TFT_STRING_MODE_NO_BACKGROUND);

	/* Display Oscilloscope Grid */
	Osc_Display_Grid();
}
