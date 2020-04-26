/*
 * DIO_prog.c
 *
 *  Created on: Dec 31, 2019
 *      Author: MO._.Hamdy "WAZEER"
 */


#include "Macros.h"
#include "DIO_Interface.h"
#include "DIO_private.h"
#include "Retval.h"


/***************************************************************************************/
/* Description! Interface to Set the direction of PIN                                  */
/* Input      ! Pin number, Desired Direction                            			   */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
uint8_t DIO_INIT_Pin(uint8_t au8_PinNumberCpy, uint8_t au8_DirectionCpy)
{
	uint8_t Error = ERROR_NOK;

	if( (au8_PinNumberCpy >= DIO_PA0)&&(au8_PinNumberCpy <= DIO_PD7)&&(au8_DirectionCpy >= INPUT_PIN)&&(au8_DirectionCpy <= OUTPUT_PIN) )
	{
		Error = ERROR_OK;
		uint8_t au8_PortNumberCpy = (au8_PinNumberCpy / BITS_PER_REGISTER);
		au8_PinNumberCpy %= BITS_PER_REGISTER;

		switch(au8_PortNumberCpy)
		{
			case DIO_PORTA:
				if(au8_DirectionCpy==OUTPUT_PIN)
				{
					SET_BIT(DDRA,au8_PinNumberCpy);
				}
				else
				{
					CLEAR_BIT(DDRA,au8_PinNumberCpy);
				}
			break;

			case DIO_PORTB:
				if(au8_DirectionCpy==OUTPUT_PIN)
				{
					SET_BIT(DDRB,au8_PinNumberCpy);
				}
				else
				{
					CLEAR_BIT(DDRB,au8_PinNumberCpy);
				}
			break;

			case DIO_PORTC:
				if(au8_DirectionCpy==OUTPUT_PIN)
				{
					SET_BIT(DDRC,au8_PinNumberCpy);
				}
				else
				{
					CLEAR_BIT(DDRC,au8_PinNumberCpy);
				}
			break;

			case DIO_PORTD:
				if(au8_DirectionCpy==OUTPUT_PIN)
				{
					SET_BIT(DDRD,au8_PinNumberCpy);
				}
				else
				{
					CLEAR_BIT(DDRD,au8_PinNumberCpy);
				}
			break;
		}
	}
	return Error;
}

/***************************************************************************************/
/* Description! Interface to set port direction                                        */
/* Input      ! Port number , Desired Direction                                        */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
uint8_t DIO_INIT_Port(uint8_t au8_PortNumberCpy,uint8_t au8_ValueCpy)
{
	uint8_t Error = ERROR_NOK;

	if( (au8_PortNumberCpy >= DIO_PORTA)&&(au8_PortNumberCpy <= DIO_PORTD)&&(au8_ValueCpy >= INPUT_PORT)&&(au8_ValueCpy <= OUTPUT_PORT) )
	{
		Error = ERROR_OK;
		switch(au8_PortNumberCpy)
		{
			case DIO_PORTA:

				DDRA = au8_ValueCpy;
			break;

			case DIO_PORTB:

				DDRB = au8_ValueCpy;
			break;

			case DIO_PORTC:

				DDRC = au8_ValueCpy;
			break;

			case DIO_PORTD:

				DDRD = au8_ValueCpy;
			break;
		}
	}
	return Error;
}

/***************************************************************************************/
/* Description! Interface to set the Output value of the pin                           */
/* Input      ! Pin number , Value to set                                			   */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
uint8_t DIO_Write_Pin(uint8_t au8_PinNumberCpy,uint8_t au8_ValueCpy)
{
	uint8_t Error = ERROR_NOK;

	if( (au8_PinNumberCpy >= DIO_PA0)&&(au8_PinNumberCpy <= DIO_PD7)&&(au8_ValueCpy >= LOW_PIN)&&(au8_ValueCpy <= HIGH_PIN) )
	{
		Error = ERROR_OK;
		uint8_t au8_PortNumberCpy = (au8_PinNumberCpy / BITS_PER_REGISTER);
		au8_PinNumberCpy %= BITS_PER_REGISTER;

		switch(au8_PortNumberCpy)
		{
			case DIO_PORTA:
				if(au8_ValueCpy==HIGH_PIN)
				{
					SET_BIT(PORTA,au8_PinNumberCpy);
				}
				else
				{
					CLEAR_BIT(PORTA,au8_PinNumberCpy);
				}
				break;
			case DIO_PORTB:
				if(au8_ValueCpy==HIGH_PIN)
				{
					SET_BIT(PORTB,au8_PinNumberCpy);
				}
				else
				{
					CLEAR_BIT(PORTB,au8_PinNumberCpy);
				}
				break;
			case DIO_PORTC:
				if(au8_ValueCpy==HIGH_PIN)
				{
					SET_BIT(PORTC,au8_PinNumberCpy);
				}
				else
				{
					CLEAR_BIT(PORTC,au8_PinNumberCpy);
				}
				break;
			case DIO_PORTD:
				if(au8_ValueCpy==HIGH_PIN)
				{
					SET_BIT(PORTD,au8_PinNumberCpy);
				}
				else
				{
					CLEAR_BIT(PORTD,au8_PinNumberCpy);
				}
				break;
		}
	}
	return Error;
}

/***************************************************************************************/
/* Description! Interface to set the output value of port                              */
/* Input      ! Port number , Desired output value                                     */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
uint8_t DIO_Write_Port(uint8_t au8_PortNumberCpy,uint8_t au8_ValueCpy)
{
	uint8_t Error = ERROR_NOK;

	if( (au8_PortNumberCpy >= DIO_PORTA )&&(au8_PortNumberCpy <= DIO_PORTD)&&(au8_ValueCpy >= LOW_PORT)&&(au8_ValueCpy <= HIGH_PORT) )
	{
		Error = ERROR_OK;
		switch(au8_PortNumberCpy)
		{
			case DIO_PORTA:

				PORTA = au8_ValueCpy; // 3shan ana bn2l data msh bs 0 aw 1
				break;

			case DIO_PORTB:

				PORTB = au8_ValueCpy;
				break;

			case DIO_PORTC:

				PORTC = au8_ValueCpy;
				break;

			case DIO_PORTD:

				PORTD = au8_ValueCpy;
				break;
		}
	}
	return Error;
}

/***************************************************************************************/
/* Description! Interface to read an input digital pin                                 */
/* Input      ! Pin number                                               			   */
/* Output     ! uint8 contains the Pin value                                           */
/***************************************************************************************/
uint8_t DIO_Read_Pin(uint8_t au8_PinNumberCpy, uint8_t * pu8_PinValueCpy)
{

	uint8_t Error = ERROR_NOK;

	if( (au8_PinNumberCpy >= DIO_PA0)&&(au8_PinNumberCpy <= DIO_PD7) )
	{
		Error = ERROR_OK;
		uint8_t au8_PortNumberCpy = (au8_PinNumberCpy / BITS_PER_REGISTER);
		au8_PinNumberCpy %= BITS_PER_REGISTER;

		switch(au8_PortNumberCpy)
		{
			case DIO_PORTA:

				*pu8_PinValueCpy = GET_BIT(PINA,au8_PinNumberCpy);
				break;
			case DIO_PORTB:

				*pu8_PinValueCpy = GET_BIT(PINB,au8_PinNumberCpy);
				break;
			case DIO_PORTC:

				*pu8_PinValueCpy = GET_BIT(PINC,au8_PinNumberCpy);
				break;
			case DIO_PORTD:

				*pu8_PinValueCpy = GET_BIT(PIND,au8_PinNumberCpy);
				break;
		}
	}
	return Error;
}

/***************************************************************************************/
/* Description! Interface to get the input value on Port                               */
/* Input      ! Port number                                                            */
/* Output     ! Port Value                                                             */
/***************************************************************************************/
uint8_t DIO_Read_Port(uint8_t au8_PortNumberCpy, uint8_t * pu8_PortValueCpy)
{
	uint8_t Error = ERROR_NOK;
	if( (au8_PortNumberCpy >= DIO_PORTA)&&(au8_PortNumberCpy <= DIO_PORTD) )
	{
		Error = ERROR_OK;
		switch(au8_PortNumberCpy)
		{
			case DIO_PORTA:

				*pu8_PortValueCpy = PINA;
			break;
			case DIO_PORTB:
				*pu8_PortValueCpy = PINB;
			break;
			case DIO_PORTC:
				*pu8_PortValueCpy = PINC;
			break;
			case DIO_PORTD:
				*pu8_PortValueCpy = PIND;
			break;
		}
	}
	return Error;
}

/***************************************************************************************/
/* Description! Interface to make pin Pullup                                           */
/* Input      ! Pin number , Value to set                                			   */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
uint8_t DIO_Pullup_Pin(uint8_t au8_PinNumberCpy)
{
	uint8_t Error = ERROR_NOK;

	if( (au8_PinNumberCpy >= DIO_PA0)&&(au8_PinNumberCpy <= DIO_PD7) )
	{
		Error = ERROR_OK;
		uint8_t au8_PortNumberCpy = (au8_PinNumberCpy / BITS_PER_REGISTER);
		au8_PinNumberCpy %= BITS_PER_REGISTER;

		switch(au8_PortNumberCpy)
		{
			case DIO_PORTA:

				SET_BIT(PORTA,au8_PinNumberCpy);
				break;
			case DIO_PORTB:

				SET_BIT(PORTB,au8_PinNumberCpy);
				break;
			case DIO_PORTC:

				SET_BIT(PORTC,au8_PinNumberCpy);
				break;
			case DIO_PORTD:

				SET_BIT(PORTD,au8_PinNumberCpy);
				break;
		}
	}
	return Error;
}

/***************************************************************************************/
/* Description! Interface to make port Pullup                                          */
/* Input      ! Port number , Desired output value                                     */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
uint8_t DIO_Pullup_Port(uint8_t au8_PortNumberCpy)
{
	uint8_t Error = ERROR_NOK;

	if( (au8_PortNumberCpy >= DIO_PORTA )&&(au8_PortNumberCpy <= DIO_PORTD) )
	{
		Error = ERROR_OK;
		switch(au8_PortNumberCpy)
		{
			case DIO_PORTA:

				PORTA = HIGH_PORT;
				break;

			case DIO_PORTB:

				PORTB = HIGH_PORT;
				break;

			case DIO_PORTC:

				PORTC = HIGH_PORT;
				break;

			case DIO_PORTD:

				PORTD = HIGH_PORT;
				break;
		}
	}
	return Error;
}
/***************************************************************************************/
/* Description! Interface to Toggle the Output value of the pin                        */
/* Input      ! Pin number , Value to set                                			   */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
uint8_t DIO_Toggle_Pin(uint8_t au8_PinNumberCpy)
{
	uint8_t Error = ERROR_NOK;

	if( (au8_PinNumberCpy >= DIO_PA0)&&(au8_PinNumberCpy <= DIO_PD7) )
	{
		Error = ERROR_OK;
		uint8_t au8_PortNumberCpy = (au8_PinNumberCpy / BITS_PER_REGISTER);
		au8_PinNumberCpy %= BITS_PER_REGISTER;

		switch(au8_PortNumberCpy)
		{
			case DIO_PORTA:
				TOGGLE_BIT(PORTA, au8_PinNumberCpy);
				break;

			case DIO_PORTB:
				TOGGLE_BIT(PORTB, au8_PinNumberCpy);
				break;

			case DIO_PORTC:
				TOGGLE_BIT(PORTC, au8_PinNumberCpy);
				break;

			case DIO_PORTD:
				TOGGLE_BIT(PORTD, au8_PinNumberCpy);
				break;
		}
	}
	return Error;
}

/***************************************************************************************/
/* Description! Interface to Toggle the output value of port                           */
/* Input      ! Port number , Desired output value                                     */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
uint8_t DIO_Toggle_Port(uint8_t au8_PortNumberCpy)
{
	uint8_t Error = ERROR_NOK;

	if( (au8_PortNumberCpy >= DIO_PORTA )&&(au8_PortNumberCpy <= DIO_PORTD) )
	{
		Error = ERROR_OK;
		switch(au8_PortNumberCpy)
		{
			case DIO_PORTA:
				TOGGLE_BYTE(PORTA);
				break;

			case DIO_PORTB:
				TOGGLE_BYTE(PORTB);
				break;

			case DIO_PORTC:
				TOGGLE_BYTE(PORTC);
				break;

			case DIO_PORTD:
				TOGGLE_BYTE(PORTD);
				break;
		}
	}
	return Error;
}
