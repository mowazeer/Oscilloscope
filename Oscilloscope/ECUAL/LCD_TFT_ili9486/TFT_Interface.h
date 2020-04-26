/*
 * TFT_Interface.h
 *
 *  Created on: Apr 20, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef TFT_INTERFACE_H_
#define TFT_INTERFACE_H_

#include "util/delay.h"
//#include "DIO_Interface.h"


/***************************************************************************************/
/* SCREEN Direction Options         		                                           */
/***************************************************************************************/
#define TFT_PORTRAIT       0U
#define TFT_LANDSCAPE      1U
#define TFT_PORTRAIT_REV   2U
#define TFT_LANDSCAPE_REV  3U

/***************************************************************************************/
/* Character Size Options         		                                        	   */
/***************************************************************************************/
#define TFT_CHAR_18_32 		0U
#define TFT_CHAR_14_24 		1U
#define TFT_CHAR_8_16 		2U

/***************************************************************************************/
/* Fill Circle Options         		                          		              	   */
/***************************************************************************************/
#define TFT_CIRCLE_R_SIDE 	0x00U
#define TFT_CIRCLE_L_SIDE 	0x01U
#define TFT_CIRCLE_FULL 	0x02U

/***************************************************************************************/
/* STRING MODE Options         		                                           		   */
/***************************************************************************************/
#define TFT_STRING_MODE_NO_BACKGROUND	0x01U
#define TFT_STRING_MODE_BACKGROUND		0x00U

/***************************************************************************************/
/* Colors Options         		                               			         	   */
/***************************************************************************************/
#define ILI9486_BLACK       0x0000
#define ILI9486_NAVY        0x000F
#define ILI9486_DARKGREEN   0x03E0
#define ILI9486_DARKCYAN    0x03EF
#define ILI9486_MAROON      0x7800
#define ILI9486_PURPLE      0x780F
#define ILI9486_OLIVE       0x7BE0
#define ILI9486_LIGHTGREY   0xC618
#define ILI9486_DARKGREY    0x7BEF
#define ILI9486_BLUE        0x001F
#define ILI9486_GREEN       0x07E0
#define ILI9486_CYAN        0x07FF
#define ILI9486_RED         0xF800
#define ILI9486_MAGENTA     0xF81F
#define ILI9486_YELLOW      0xFFE0
#define ILI9486_WHITE       0xFFFF
#define ILI9486_ORANGE      0xFD20
#define ILI9486_GREENYELLOW 0xAFE5
#define ILI9486_PINK        0xF81F

/***************************************************************************************/
/* TFT Provided FUNCTIONS for USER		         		                               */
/***************************************************************************************/

extern void TFT_Init(void);
extern void TFT_ClearDisplay(uint16_t color);

/***************************************************************************************/
/* Draw FUNCTIONS         		                         		      				   */
/***************************************************************************************/
extern void TFT_Draw_VLine(uint16_t au16_X, uint16_t au16_Y, uint16_t au16_Hight, uint16_t color);
extern void TFT_Draw_HLine(uint16_t au16_X, uint16_t au16_Y, uint16_t au16_Width, uint16_t au16_color);
extern void TFT_Draw_CLine(uint16_t au16_X0, uint16_t au16_Y0, uint16_t au16_X1, uint16_t au16_Y1, uint16_t au16_color);

extern void TFT_Draw_Circle(uint16_t au16_X0, uint16_t au16_Y0, uint16_t au16_Radius, uint16_t au16_Color);
extern void TFT_Fill_Circle(uint16_t au16_X0, uint16_t au16_Y0, uint16_t au16_Radius, uint8_t au8_Side, uint16_t au16_Color);

extern void TFT_Draw_Rect(uint16_t au16_X, uint16_t au16_Y,  uint16_t au16_Width, uint16_t au16_Hight,  uint16_t au16_Color);
extern void TFT_Fill_Rect(uint16_t au16_X, uint16_t au16_Y, uint16_t au16_Width, uint16_t au16_Hight, uint16_t au16_Color);
extern void TFT_Fill_Screen(uint16_t au16_Color);

/***************************************************************************************/
/* TEXT PRINT FUNCTIONS         		                               				   */
/***************************************************************************************/
extern void TFT_SetCursor(uint16_t au16_X, uint16_t au16_Y);
extern void TFT_SetTextColor(uint16_t au16_Point_C, uint16_t au16_Back_C);
extern void TFT_Print_String(uint8_t *pu8_Str, uint8_t au8_Char_Size, uint8_t au8_TFT_Str_Mode);
extern void TFT_Print_Number(sint32_t  as32_Num, uint8_t au8_Char_Size, uint8_t au8_TFT_Str_Mode);



#endif /* TFT_INTERFACE_H_ */
