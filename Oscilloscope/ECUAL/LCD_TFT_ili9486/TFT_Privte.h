/*
 * TFT_Privte.h
 *
 *  Created on: Apr 20, 2020
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef TFT_PRIVTE_H_
#define TFT_PRIVTE_H_


/***************************************************************************************/
/* SCREEN SIZE         		                                                           */
/***************************************************************************************/
#define TFT_WIDTH  	320UL
#define TFT_HIGHT 	480UL

/***************************************************************************************/
/* SCREEN Direction COMMANDS         		                                           */
/***************************************************************************************/
#define PORTRAIT       0x48U
#define LANDSCAPE      0x28U
#define PORTRAIT_REV   0x98U
#define LANDSCAPE_REV  0xF4U

/***************************************************************************************/
/* SCREEN COMMANDS  			       		                                           */
/***************************************************************************************/
#define TFT_NOP     0x00U
#define TFT_SWRST   0x01U
#define TFT_CASET   0x2AU
#define TFT_PASET   0x2BU
#define TFT_RAMWR   0x2CU
#define TFT_RAMRD   0x2EU
#define TFT_MADCTL  0x36U
#define TFT_MAD_MY  0x80U
#define TFT_MAD_MX  0x40U
#define TFT_MAD_MV  0x20U
#define TFT_MAD_ML  0x10U
#define TFT_MAD_BGR 0x08U
#define TFT_MAD_MH  0x04U
#define TFT_MAD_SS  0x02U
#define TFT_MAD_GS  0x01U
#define TFT_MAD_RGB 0x00U
#define TFT_INVOFF  0x20U
#define TFT_INVON   0x21U

/***************************************************************************************/
/* TFT PRIVTE FUNCTIONS USER CANNOT USE IT         		                               */
/***************************************************************************************/
//static void WRITE_DATA(uint8_t data);
//static void Write_Byte(uint8_t data);
static void TFT_Write_Data_Byte(uint8_t au8_Data);
//static void TFT_Write_Data_Word(uint16_t au8_Data);

static void TFT_Write_Cmd_Byte(uint8_t au8_cmd);
//static void TFT_Write_Cmd_Word(uint16_t au16_cmd);

//static void TFT_Write_Cmd_Str_Byte(uint8_t au8_cmd, uint8_t au8_Size, uint8_t * au8_Data_Word);
static void TFT_Write_Cmd_Str_Word(uint8_t au8_cmd, uint8_t au8_Size, uint16_t * pu16_Data_Word);

static void TFT_Draw_Pixel(uint16_t au16_X, uint16_t au16_Y, uint16_t au16_Color);

static void TFT_SetAddrWindow(uint16_t au16_X, uint16_t au16_Y, uint16_t au16_X1, uint16_t au16_Y1);

static void TFT_Print_Char(uint16_t au16_X, uint16_t au16_Y, uint8_t au8_Char_Size, uint8_t au8_Data, uint8_t au8_Mode);

static void TFT_Reset(void);
static void TFT_Set_Rotation(void);

#endif /* TFT_PRIVTE_H_ */
