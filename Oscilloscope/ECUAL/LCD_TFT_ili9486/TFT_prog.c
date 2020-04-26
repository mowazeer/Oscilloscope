 /*
  * LCD_TFT_prog.c
  *
  *  Created on: Apr 20, 2020
  *      Author: MO._.Hamdy "Wazeer"
  */
#include "Data_Types.h"
#include "Macros.h"
#include "avr/pgmspace.h"
#include "TFT_Interface.h"
#include "TFT_cfg.h"
#include "TFT_Privte.h"
#include "TFT_Fonts.h"


/*
 *	GLOBALE variables that hold the Screen Width & Height
 */
uint16_t gu16_TFT_W = TFT_WIDTH;
uint16_t gu16_TFT_H = TFT_HIGHT;

/*
 *	GLOBALE variables that hold the Cursor X_Y position
 */
uint16_t gu16_Cursor_X;
uint16_t gu16_Cursor_Y;

/*
 *	GLOBALE variables that hold the Screen Point & Back Color
 */
uint16_t gu16_Point_Color;
uint16_t gu16_Back_Color;

/***************************************************************************************/
/* TFT PRIVTE FUNCTIONS USER CANNOT USE IT         		                               */
/***************************************************************************************/
#define WRITE_DATA(Data)	do{ TFT_DATA_PORT = Data;\
								CLEAR_BIT(TFT_CTRL_PORT,TFT_WR);\
								SET_BIT(TFT_CTRL_PORT,TFT_WR);\
								}while(0)// WRITE DATA // WR_ACTIVE // WR_IDLE
/*
static void WRITE_DATA(uint8_t data)
{
	// WRITE DATA
	TFT_DATA_PORT=data;

	// WR_ACTIVE
	CLEAR_BIT(TFT_CTRL_PORT,TFT_WR);

	// WR_IDLE
	SET_BIT(TFT_CTRL_PORT,TFT_WR);

}
*/
/*
#define TFT_Write_Data_Byte(data) 	do{ CLEAR_BIT(TFT_CTRL_PORT,TFT_CS);\
										SET_BIT(TFT_CTRL_PORT,TFT_RS);\
										WRITE_DATA(data);\
										SET_BIT(TFT_CTRL_PORT,TFT_CS);\
										}while(0)
*/
static void TFT_Write_Data_Byte(uint8_t au8_Data)
{
	// CS_ACTIVE
	CLEAR_BIT(TFT_CTRL_PORT,TFT_CS);

	// CD/RS DATA
	SET_BIT(TFT_CTRL_PORT,TFT_RS);

	WRITE_DATA(au8_Data);

	// CS_IDLE
	SET_BIT(TFT_CTRL_PORT,TFT_CS);
}
#define TFT_Write_Data_Word(au8_Data) 	do{ CLEAR_BIT(TFT_CTRL_PORT,TFT_CS);\
											SET_BIT(TFT_CTRL_PORT,TFT_RS);\
											WRITE_DATA(au8_Data >> 8U );\
											WRITE_DATA(au8_Data & 0x00FFU );\
											SET_BIT(TFT_CTRL_PORT,TFT_CS);\
											}while(0)
/*
static void TFT_Write_Data_Word(uint16_t au8_Data)
{
	// CS_ACTIVE
	CLEAR_BIT(TFT_CTRL_PORT,TFT_CS);

	// CD/RS DATA
	SET_BIT(TFT_CTRL_PORT,TFT_RS);

	WRITE_DATA(au8_Data >> 8U );
	WRITE_DATA(au8_Data & 0x00FFU );

	// CS_IDLE
	SET_BIT(TFT_CTRL_PORT,TFT_CS);
}
*/
static void TFT_Write_Cmd_Byte(uint8_t au8_cmd)
{
	// CS_ACTIVE
	CLEAR_BIT(TFT_CTRL_PORT,TFT_CS);

	// CD/RS COMMAND
	CLEAR_BIT(TFT_CTRL_PORT,TFT_RS);

	WRITE_DATA(au8_cmd);

	// CS_IDLE
	SET_BIT(TFT_CTRL_PORT,TFT_CS);
}

/* for future use
static void TFT_Write_Cmd_Word(uint16_t au16_cmd)
{

	// CS_ACTIVE
	CLEAR_BIT(TFT_CTRL_PORT,TFT_CS);

	// CD/RS COMMAND
	CLEAR_BIT(TFT_CTRL_PORT,TFT_RS);

	WRITE_DATA(au16_cmd >> 8U );
	WRITE_DATA(au16_cmd & 0x00FFU );

	// CS_IDLE
	SET_BIT(TFT_CTRL_PORT,TFT_CS);
}
*/
/* for future use
static void TFT_Write_Cmd_Str_Byte(uint8_t au8_cmd, uint8_t au8_Size, uint8_t * au8_Data_Byte)
{
	TFT_Write_Cmd_Byte(au8_cmd);

	while (au8_Size-- > NULL)
	{
		TFT_Write_Data_Byte(*au8_Data_Byte ++);;
	}
}
*/
static void TFT_Write_Cmd_Str_Word(uint8_t au8_cmd, uint8_t au8_Size, uint16_t * pu16_Data_Word)
{
	TFT_Write_Cmd_Byte(au8_cmd);

	while (au8_Size-- > NULL)
	{
		TFT_Write_Data_Word(*pu16_Data_Word ++);
	}
}

static void TFT_Draw_Pixel(uint16_t au16_X, uint16_t au16_Y, uint16_t au16_Color)
{


	if ((NULL > au16_X) || (NULL > au16_Y) || (gu16_TFT_W <= au16_X) || (gu16_TFT_H <= au16_Y))
	{
		return;
	}

	TFT_Write_Cmd_Byte(TFT_CASET);
	TFT_Write_Data_Word(au16_X);
	TFT_Write_Data_Word(au16_X);

	TFT_Write_Cmd_Byte(TFT_PASET);
	TFT_Write_Data_Word(au16_Y);
	TFT_Write_Data_Word(au16_Y);

	TFT_Write_Cmd_Str_Word(TFT_RAMWR, 1U, &au16_Color);
}

static void TFT_SetAddrWindow(uint16_t au16_X, uint16_t au16_Y, uint16_t au16_X1, uint16_t au16_Y1)
{
	TFT_Write_Cmd_Byte(TFT_CASET);
	TFT_Write_Data_Word(au16_X);
	TFT_Write_Data_Word(au16_X1);

	TFT_Write_Cmd_Byte(TFT_PASET);
	TFT_Write_Data_Word(au16_Y);
	TFT_Write_Data_Word(au16_Y1);
}

static void TFT_Print_Char(uint16_t au16_X, uint16_t au16_Y, uint8_t au8_Char_Size, uint8_t au8_Data, uint8_t au8_Mode)
{
	uint8_t u8_Count,j,k,temp;

	uint8_t au8_tftChar_W;
	uint8_t au8_tftChar_H;

	switch(au8_Char_Size)
	{
		case TFT_CHAR_18_32 :

			au8_tftChar_W = 18U;
			au8_tftChar_H = 32U;

			if((au16_X > (gu16_TFT_W - au8_tftChar_W))||(au16_Y > (gu16_TFT_H - au8_tftChar_H)))
			{
				return;
			}
			TFT_SetAddrWindow(au16_X, au16_Y, au16_X+au8_tftChar_W-1, au16_Y+au8_tftChar_H-1);

			for(u8_Count=0;u8_Count<au8_tftChar_H/8;u8_Count++)
			{
				for(j=0;j<8;j++)
				{
					for(k=0;k<au8_tftChar_W;k++)
					{
						temp = pgm_read_byte(&(Consolas18x32[(au8_Data-' ')*(au8_tftChar_H/8)*au8_tftChar_W+k*(au8_tftChar_H/8)+u8_Count]));          //temp=Consolas18x32[(au8_Data-' ')*(32/8)*18+k*(32/8)+u8_Count];
						if(au8_Mode==TFT_STRING_MODE_BACKGROUND)
						{
							if(temp&(0x01<<j))
							{
								TFT_Write_Data_Word(gu16_Point_Color);
							}
							else
							{
								TFT_Write_Data_Word(gu16_Back_Color);
							}
						}
						else
						{
							if(temp&(0x01<<j))
							{
								TFT_Draw_Pixel(au16_X+k,au16_Y+(8*u8_Count+j),gu16_Point_Color);
							}
						}
					}
				}
			}
		break;

		case TFT_CHAR_14_24 :

			au8_tftChar_W = 14U;
			au8_tftChar_H = 24U;

			if((au16_X > (gu16_TFT_W - au8_tftChar_W))||(au16_Y > (gu16_TFT_H - au8_tftChar_H)))
			{
				return;
			}
			TFT_SetAddrWindow(au16_X, au16_Y, au16_X+au8_tftChar_W-1, au16_Y+au8_tftChar_H-1);

			for(u8_Count=0;u8_Count<au8_tftChar_H/8;u8_Count++)
			{
				for(j=0;j<8;j++)
				{
					for(k=0;k<au8_tftChar_W;k++)
					{
						temp = pgm_read_byte(&(Consolas14x24[(au8_Data-' ')*(au8_tftChar_H/8)*au8_tftChar_W+k*(au8_tftChar_H/8)+u8_Count]));      // temp=Consolas14x24[(au8_Data-' ')*(24/8)*14+k*(24/8)+u8_Count];
						if(au8_Mode==TFT_STRING_MODE_BACKGROUND)
						{
							if(temp&(0x01<<j))
							{
								TFT_Write_Data_Word(gu16_Point_Color);
							}
							else
							{
								TFT_Write_Data_Word(gu16_Back_Color);
							}
						}
						else
						{
							if(temp&(0x01<<j))
							{
								TFT_Draw_Pixel(au16_X+k,au16_Y+(8*u8_Count+j),gu16_Point_Color);
							}
						}
					}
				}
			}
		break;

		case TFT_CHAR_8_16 :

			au8_tftChar_W = 8U;
			au8_tftChar_H = 16U;

			if((au16_X > (gu16_TFT_W - au8_tftChar_W))||(au16_Y > (gu16_TFT_H - au8_tftChar_H)))
			{
				return;
			}
			TFT_SetAddrWindow(au16_X, au16_Y, au16_X+au8_tftChar_W-1, au16_Y+au8_tftChar_H-1);

			au8_Data = au8_Data - ' ';

			if(!au8_Mode)
			{
				for(u8_Count=0;u8_Count<16;u8_Count++)
				{
					temp = pgm_read_byte(&(asc2_1608[(uint16_t)au8_Data*16+u8_Count]));       // temp=asc2_1608[(uint16_t)num*16+u8_Count];
					for(j=0;j<8;j++)
					{
						if(temp&0x01)
						{
							TFT_Write_Data_Word(gu16_Point_Color);
						}
						else
						{
							TFT_Write_Data_Word(gu16_Back_Color);
						}
						temp>>=1;
					}
				}
			}
			else
			{
				for(u8_Count=0;u8_Count<16;u8_Count++)
				{
					temp = pgm_read_byte(&(asc2_1608[(uint16_t)au8_Data*16+u8_Count]));       //temp=asc2_1608[(uint16_t)num*16+u8_Count];
					for(j=0;j<8;j++)
					{
						if(temp&0x01)TFT_Draw_Pixel(au16_X+j,au16_Y+u8_Count,gu16_Point_Color);
						temp>>=1;
					}
				}
			}
		break;
	}
}

static void TFT_Reset()
{

	/* CS_IDLE */
	SET_BIT(TFT_CTRL_PORT,TFT_CS);

	/* RD_IDLE */
	SET_BIT(TFT_CTRL_PORT,TFT_RD);

	/* WR_IDLE */
	SET_BIT(TFT_CTRL_PORT,TFT_WR);

	/* RESET_IDLE */
	SET_BIT(TFT_CTRL_PORT,TFT_RST);

	_delay_ms(50);

	/* RESET_IDLE */
	CLEAR_BIT(TFT_CTRL_PORT,TFT_RST);

	_delay_ms(50);

	/* RESET_IDLE */
	SET_BIT(TFT_CTRL_PORT,TFT_RST);

	_delay_ms(50);

}

static void TFT_Set_Rotation(void)
{

	TFT_Write_Cmd_Byte(0x36);

	#if(TFT_DISPLAY_MODE == TFT_PORTRAIT)

		TFT_Write_Data_Byte(PORTRAIT);
		gu16_TFT_W = TFT_WIDTH;
		gu16_TFT_H = TFT_HIGHT;

	#elif(TFT_DISPLAY_MODE == TFT_LANDSCAPE)

		TFT_Write_Data_Byte(LANDSCAPE);
		gu16_TFT_W = TFT_HIGHT;
		gu16_TFT_H = TFT_WIDTH;

	#elif(TFT_DISPLAY_MODE == TFT_PORTRAIT_REV)

		TFT_Write_Data_Byte(PORTRAIT_REV);
		gu16_TFT_W = TFT_WIDTH;
		gu16_TFT_H = TFT_HIGHT;
		break;

#elif(TFT_DISPLAY_MODE == TFT_LANDSCAPE_REV)

		TFT_Write_Data_Byte(LANDSCAPE_REV);
		gu16_TFT_W = TFT_HIGHT;
		gu16_TFT_H = TFT_WIDTH;
	#endif
}

/***************************************************************************************/
/***************************************************************************************/
/* TFT Provided FUNCTIONS for USER		         		                               */
/***************************************************************************************/
/***************************************************************************************/
void TFT_Init(void)
{
	/* SET CONTROL PINS OUTPUT */
	SET_BIT(TFT_CTRL_PORT_DIR,TFT_WR);
	SET_BIT(TFT_CTRL_PORT_DIR,TFT_RS);
	SET_BIT(TFT_CTRL_PORT_DIR,TFT_CS);
	SET_BIT(TFT_CTRL_PORT_DIR,TFT_RD);
	SET_BIT(TFT_CTRL_PORT_DIR,TFT_RST);
	/* SET DATA PINS OUTPUT */
	TFT_DATA_PORT_DIR = 0xFF ;

	TFT_Reset();

	TFT_Write_Cmd_Byte(0x11); // Sleep out, also SW reset
	_delay_ms(50);

	TFT_Write_Cmd_Byte(0x3A);
	TFT_Write_Data_Byte(0x55);

	TFT_Write_Cmd_Byte(0xC2);
	TFT_Write_Data_Byte(0x44);

	TFT_Write_Cmd_Byte(0xC5);
	TFT_Write_Data_Byte(0x00);
	TFT_Write_Data_Byte(0x00);
	TFT_Write_Data_Byte(0x00);
	TFT_Write_Data_Byte(0x00);

	TFT_Write_Cmd_Byte(0xE0);
	TFT_Write_Data_Byte(0x0F);
	TFT_Write_Data_Byte(0x1F);
	TFT_Write_Data_Byte(0x1C);
	TFT_Write_Data_Byte(0x0C);
	TFT_Write_Data_Byte(0x0F);
	TFT_Write_Data_Byte(0x08);
	TFT_Write_Data_Byte(0x48);
	TFT_Write_Data_Byte(0x98);
	TFT_Write_Data_Byte(0x37);
	TFT_Write_Data_Byte(0x0A);
	TFT_Write_Data_Byte(0x13);
	TFT_Write_Data_Byte(0x04);
	TFT_Write_Data_Byte(0x11);
	TFT_Write_Data_Byte(0x0D);
	TFT_Write_Data_Byte(0x00);

	TFT_Write_Cmd_Byte(0xE1);
	TFT_Write_Data_Byte(0x0F);
	TFT_Write_Data_Byte(0x32);
	TFT_Write_Data_Byte(0x2E);
	TFT_Write_Data_Byte(0x0B);
	TFT_Write_Data_Byte(0x0D);
	TFT_Write_Data_Byte(0x05);
	TFT_Write_Data_Byte(0x47);
	TFT_Write_Data_Byte(0x75);
	TFT_Write_Data_Byte(0x37);
	TFT_Write_Data_Byte(0x06);
	TFT_Write_Data_Byte(0x10);
	TFT_Write_Data_Byte(0x03);
	TFT_Write_Data_Byte(0x24);
	TFT_Write_Data_Byte(0x20);
	TFT_Write_Data_Byte(0x00);

	TFT_Write_Cmd_Byte(0x20);                     // display inversion OFF

	TFT_Write_Cmd_Byte(0x36);
	TFT_Write_Data_Byte(0x48);

	TFT_Write_Cmd_Byte(0x29);                     // display on
	_delay_ms(50);

	TFT_Set_Rotation();
}

void TFT_ClearDisplay(uint16_t au16_Color)
{
	uint16_t Row,Col;

	TFT_SetAddrWindow(INITIAL, INITIAL, gu16_TFT_W -1U, gu16_TFT_H -1U);
	TFT_Write_Cmd_Byte(TFT_RAMWR);

	for(Row = NULL; Row < gu16_TFT_W; Row++)
	{
		for (Col = NULL; Col < gu16_TFT_H; Col++)
		{
			TFT_Write_Data_Word(au16_Color);
		}
	}
}

/***************************************************************************************/
/* Draw FUNCTIONS         		                         		      				   */
/***************************************************************************************/
void TFT_Fill_Rect(uint16_t au16_X, uint16_t au16_Y, uint16_t au16_Width, uint16_t au16_Hight, uint16_t au16_Color)
{
	uint16_t u16_Max;

	u16_Max = au16_X + au16_Width;
	if (u16_Max > gu16_TFT_W)
	{
		u16_Max = gu16_TFT_W;
		au16_Width = u16_Max - au16_X;
	}

	u16_Max = au16_Y + au16_Hight;
	if (u16_Max > gu16_TFT_H)
	{
		u16_Max = gu16_TFT_H;
		au16_Hight = u16_Max - au16_Y;
	}

	TFT_SetAddrWindow(au16_X, au16_Y, au16_X + au16_Width - 1U, au16_Y + au16_Hight - 1U);
	TFT_Write_Cmd_Byte(TFT_RAMWR);

	while (au16_Hight-- > NULL)
	{
		u16_Max = au16_Width;
		do{
			TFT_Write_Data_Word(au16_Color);
		} while (--u16_Max != NULL);
	}

}

void TFT_Fill_Screen(uint16_t au16_Color)
{
	TFT_Fill_Rect(INITIAL, INITIAL, gu16_TFT_W, gu16_TFT_H, au16_Color);
}

void TFT_Draw_VLine(uint16_t au16_X, uint16_t au16_Y, uint16_t au16_Hight, uint16_t color)
{
	if ((au16_X >= gu16_TFT_W) || (au16_Y >= gu16_TFT_H) || (au16_Hight < 1U))
	{
		return;
	}

	if ((au16_Y + au16_Hight - 1U) >= gu16_TFT_H)
	{
		au16_Hight = gu16_TFT_H - au16_Y;
	}

	TFT_Fill_Rect(au16_X, au16_Y, 1, au16_Hight, color);
}

void TFT_Draw_HLine(uint16_t au16_X, uint16_t au16_Y, uint16_t au16_Width, uint16_t au16_color)
{
	if ((au16_X >= gu16_TFT_W) || (au16_Y >= gu16_TFT_H) || (au16_Width < 1U))
	{
		return;
	}

	if ((au16_X + au16_Width - 1U) >=gu16_TFT_W)
	{
		au16_Width = gu16_TFT_W - au16_X;
	}

	TFT_Fill_Rect(au16_X, au16_Y, au16_Width, 1, au16_color);
}

void TFT_Draw_CLine(uint16_t au16_X0, uint16_t au16_Y0, uint16_t au16_X1, uint16_t au16_Y1, uint16_t au16_color)
{

	uint8_t u8_Count;
	uint16_t u16_Diff_x,u16_Diff_y;
	sint8_t s8_Sign_x,s8_Sign_y;
	sint16_t E;

	/* distance between two points */
	if(au16_X1 > au16_X0)
	{
		u16_Diff_x = au16_X1 - au16_X0 ;
		s8_Sign_x = 1 ;
	}
	else
	{
		u16_Diff_x = au16_X0 - au16_X1 ;
		s8_Sign_x = -1 ;
	}

	if(au16_Y1 > au16_Y0)
	{
		u16_Diff_y = au16_Y1 - au16_Y0 ;
		s8_Sign_y = 1 ;
	}
	else
	{
		u16_Diff_y = au16_Y0 - au16_Y1 ;
		s8_Sign_y = -1;
	}

	if (au16_Y0 == au16_Y1)
	{
		if (au16_X1 > au16_X0)
		{
			TFT_Draw_HLine(au16_X0, au16_Y0, au16_X1 - au16_X0 + 1, au16_color);
		}
		else
		{
			TFT_Draw_HLine(au16_X1, au16_Y0, au16_X0 - au16_X1 + 1, au16_color);
		}
		return;
	}
	else if (au16_X0 == au16_X1)
	{
		if (au16_Y1 > au16_Y0)
		{
			TFT_Draw_VLine(au16_X0, au16_Y0, au16_Y1 - au16_Y0 + 1, au16_color);
		}
		else
		{
			TFT_Draw_VLine(au16_X0, au16_Y1, au16_Y0 - au16_Y1 + 1, au16_color);
		}
		return;
	}

	/* inclination < 1 */
	if ( u16_Diff_x > u16_Diff_y )
	{
		E = -u16_Diff_x;
		for ( u8_Count = 0 ; u8_Count <= u16_Diff_x ; u8_Count++ )
		{
			TFT_Draw_Pixel( au16_X0, au16_Y0, au16_color );
			au16_X0 += s8_Sign_x;
			E += 2 * u16_Diff_y;
			if ( E >= 0 )
			{
				au16_Y0 += s8_Sign_y;
				E -= 2 * u16_Diff_x;
			}
		}
	}
	/* inclination >= 1 */
	else
	{
		E = -u16_Diff_y;
		for ( u8_Count = 0 ; u8_Count <= u16_Diff_y ; u8_Count++ )
		{
			TFT_Draw_Pixel( au16_X0, au16_Y0, au16_color );
			au16_Y0 += s8_Sign_y;
			E += 2 * u16_Diff_x;
			if ( E >= 0 )
			{
				au16_X0 += s8_Sign_x;
				E -= 2 * u16_Diff_y;
			}
		}
	}
}

void TFT_Draw_Circle(uint16_t au16_X0, uint16_t au16_Y0, uint16_t au16_Radius, uint16_t au16_Color)
{
	sint16_t f = 1 - au16_Radius;
	sint16_t ddF_x = 1;
	sint16_t ddF_y = -2 * au16_Radius;
	uint16_t x = 0;
	uint16_t y = au16_Radius;

	TFT_Draw_Pixel(au16_X0  , au16_Y0 + au16_Radius, au16_Color);
	TFT_Draw_Pixel(au16_X0  , au16_Y0 - au16_Radius, au16_Color);
	TFT_Draw_Pixel(au16_X0 + au16_Radius, au16_Y0  , au16_Color);
	TFT_Draw_Pixel(au16_X0 - au16_Radius, au16_Y0  , au16_Color);

	while (x < y)
	{

		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}

		x++;
		ddF_x += 2;
		f += ddF_x;

		TFT_Draw_Pixel(au16_X0 + x, au16_Y0 + y, au16_Color);
		TFT_Draw_Pixel(au16_X0 - x, au16_Y0 + y, au16_Color);
		TFT_Draw_Pixel(au16_X0 + x, au16_Y0 - y, au16_Color);
		TFT_Draw_Pixel(au16_X0 - x, au16_Y0 - y, au16_Color);
		TFT_Draw_Pixel(au16_X0 + y, au16_Y0 + x, au16_Color);
		TFT_Draw_Pixel(au16_X0 - y, au16_Y0 + x, au16_Color);
		TFT_Draw_Pixel(au16_X0 + y, au16_Y0 - x, au16_Color);
		TFT_Draw_Pixel(au16_X0 - y, au16_Y0 - x, au16_Color);
	}
}

void TFT_Fill_Circle(uint16_t au16_X0, uint16_t au16_Y0, uint16_t au16_Radius, uint8_t au8_Side, uint16_t au16_Color)
{
	sint16_t f     = 1 - au16_Radius;
	sint16_t ddF_x = 1;
	sint16_t ddF_y = (-2) * au16_Radius;
	uint16_t u16_X = 0U;
	uint16_t u16_Y = au16_Radius;

	TFT_Draw_VLine(au16_X0, au16_Y0 - au16_Radius, (2* au16_Radius) +1, au16_Color);

	while (u16_X < u16_Y)
	{
		if (f >= 0)
		{
			u16_Y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		u16_X++;
		ddF_x += 2;
		f     += ddF_x;

		switch(au8_Side)
		{
			case TFT_CIRCLE_R_SIDE:

				TFT_Draw_VLine(au16_X0+u16_X, au16_Y0 - u16_Y, (2*u16_Y) +1, au16_Color);
				TFT_Draw_VLine(au16_X0+u16_Y, au16_Y0 - u16_X, (2*u16_X) +1, au16_Color);
			break;

			case TFT_CIRCLE_L_SIDE:

				TFT_Draw_VLine(au16_X0-u16_X, au16_Y0 - u16_Y, (2*u16_Y) +1, au16_Color);
				TFT_Draw_VLine(au16_X0-u16_Y, au16_Y0 - u16_X, (2*u16_X) +1, au16_Color);
			break;

			case TFT_CIRCLE_FULL:

				TFT_Draw_VLine(au16_X0+u16_X, au16_Y0 - u16_Y, (2*u16_Y) +1, au16_Color);
				TFT_Draw_VLine(au16_X0+u16_Y, au16_Y0 - u16_X, (2*u16_X) +1, au16_Color);

				TFT_Draw_VLine(au16_X0-u16_X, au16_Y0 - u16_Y, (2*u16_Y) +1, au16_Color);
				TFT_Draw_VLine(au16_X0-u16_Y, au16_Y0 - u16_X, (2*u16_X) +1, au16_Color);
			break;
		}
	}
}

void TFT_Draw_Rect(uint16_t au16_X, uint16_t au16_Y,  uint16_t au16_Width, uint16_t au16_Hight,  uint16_t au16_Color)
{
	TFT_Draw_HLine(au16_X, au16_Y, au16_Width, au16_Color);
	TFT_Draw_HLine(au16_X, au16_Y + au16_Hight -1U, au16_Width, au16_Color);

	TFT_Draw_VLine(au16_X, au16_Y, au16_Hight, au16_Color);
	TFT_Draw_VLine(au16_X + au16_Width -1U, au16_Y, au16_Hight, au16_Color);
}

/***************************************************************************************/
/* TEXT PRINT FUNCTIONS         		                               				   */
/***************************************************************************************/
void TFT_SetCursor(uint16_t au16_X, uint16_t au16_Y)
{
	#if(TFT_DISPLAY_MODE == TFT_PORTRAIT)

		gu16_Cursor_X = au16_X;
		gu16_Cursor_Y = au16_Y;

	#elif(TFT_DISPLAY_MODE == TFT_LANDSCAPE)

		gu16_Cursor_X = au16_Y;
		gu16_Cursor_Y = au16_X;

	#elif(TFT_DISPLAY_MODE == TFT_PORTRAIT_REV)
			gu16_Cursor_X = au16_X + TFT_WIDTH;
			gu16_Cursor_Y = au16_Y + TFT_HIGHT;

	#elif(TFT_DISPLAY_MODE == TFT_LANDSCAPE_REV)
			gu16_Cursor_X = au16_Y + TFT_HIGHT;
			gu16_Cursor_Y = au16_X + TFT_WIDTH;
	#endif
}


void TFT_SetTextColor(uint16_t au16_Point_C, uint16_t au16_Back_C)
{
	gu16_Point_Color = au16_Point_C;
	gu16_Back_Color  = au16_Back_C;
}

void TFT_Print_String(uint8_t *pu8_Str, uint8_t au8_Char_Size, uint8_t au8_TFT_Str_Mode)
{
	uint8_t u8_index = INITIAL;
	uint8_t u8_Font_W;
	uint8_t u8_Font_H;

	switch(au8_Char_Size)
	{
		case TFT_CHAR_18_32 :

			u8_Font_W = 18U;
			u8_Font_H = 32U;
		break;

		case TFT_CHAR_14_24 :

			u8_Font_W = 14U;
			u8_Font_H = 24U;
		break;

		case TFT_CHAR_8_16 :

			u8_Font_W = 8U;
			u8_Font_H = 16U;
		break;
	}

	while(pu8_Str[u8_index]!= '\0')
	{
		if(gu16_Cursor_Y > (gu16_TFT_W - u8_Font_W))
		{
			gu16_Cursor_Y = INITIAL;
			gu16_Cursor_X += u8_Font_H;
		}

		if(gu16_Cursor_X > (gu16_TFT_H - u8_Font_H))
		{
			gu16_Cursor_X = INITIAL;
			gu16_Cursor_Y = INITIAL;
		}

		TFT_Print_Char(gu16_Cursor_Y, gu16_Cursor_X, au8_Char_Size,pu8_Str[u8_index], au8_TFT_Str_Mode);
		gu16_Cursor_Y += u8_Font_W;
		u8_index++;
	}
}

void TFT_Print_Number(sint32_t  as32_Num, uint8_t au8_Char_Size, uint8_t au8_TFT_Str_Mode)
{

	uint32_t u32_Num_Rev = 1L;
	uint32_t u32_Reminder_1 = INITIAL;
	uint32_t u32_Reminder_2 = INITIAL;

	uint8_t u8_Font_W;
	uint8_t u8_Font_H;

	switch(au8_Char_Size)
	{
		case TFT_CHAR_18_32 :

			u8_Font_W = 18U;
			u8_Font_H = 32U;
		break;

		case TFT_CHAR_14_24 :

			u8_Font_W = 14U;
			u8_Font_H = 24U;
		break;

		case TFT_CHAR_8_16 :

			u8_Font_W = 8U;
			u8_Font_H = 16U;
		break;
	}

	if(gu16_Cursor_Y > (gu16_TFT_W - u8_Font_W))
	{
		gu16_Cursor_Y = INITIAL;
		gu16_Cursor_X += u8_Font_H;
	}

	if(gu16_Cursor_X > (gu16_TFT_H - u8_Font_H))
	{
		gu16_Cursor_X = INITIAL;
		gu16_Cursor_Y = INITIAL;
	}

	switch(as32_Num)
	{
		case 0U:
			TFT_Print_Char(gu16_Cursor_Y, gu16_Cursor_X, au8_Char_Size, '0', au8_TFT_Str_Mode);
			gu16_Cursor_Y += u8_Font_W;
		break;
		default:
			if(0U > as32_Num)
			{
				TFT_Print_Char(gu16_Cursor_Y, gu16_Cursor_X, au8_Char_Size, '-', au8_TFT_Str_Mode);
				gu16_Cursor_Y += u8_Font_W;
			}
			while (as32_Num)
			{
				u32_Reminder_1 = as32_Num % 10;
				as32_Num      /= 10 ;
				u32_Num_Rev    = (u32_Num_Rev *10) + u32_Reminder_1 ;
			}
			while (u32_Num_Rev != 1U)
			{
				u32_Reminder_2 = u32_Num_Rev % 10 ;

				TFT_Print_Char(gu16_Cursor_Y, gu16_Cursor_X, au8_Char_Size,u32_Reminder_2 +'0', au8_TFT_Str_Mode);
				gu16_Cursor_Y += u8_Font_W;

				u32_Num_Rev /= 10 ;
			}
		break;
	}
}
