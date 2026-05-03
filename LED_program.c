/*
 * LED_program.c
 *
 * Created: 11/24/2025 1:33:17 PM
 *  Author: hamza
 */ 

/*UTILES Lib*/
#include "STD_types.h"
#include "Bit_Math.h"

/*MCAL*/
#include "DIO_interface.h"

/*MAL*/
#include "LED_inteface.h"

void LED_voidInit  (u8 copy_u8LedPort ,u8 copy_u8LedPin)
{
	DIO_voidSetPinDirection(copy_u8LedPort , copy_u8LedPin ,DIO_PIN_OUTPUT);
}

void LED_voidOn    (u8 copy_u8LedPort ,u8 copy_u8LedPin , u8 copy_u8LedConnectionType)
{
	switch(copy_u8LedConnectionType)
	{
		case LED_FORWARD_CONNECTION:
		DIO_voidGetPinValue(copy_u8LedPort , copy_u8LedPin , DIO_PIN_HIGH);
		break;
		
		case LED_REVERSE_CONNECTION:
		DIO_voidGetPinValue(copy_u8LedPort , copy_u8LedPin , DIO_PIN_LOW);
		break;
	}
}

void LED_voidOff   (u8 copy_u8LedPort ,u8 copy_u8LedPin , u8 copy_u8LedConnectionType)
{
	switch(copy_u8LedConnectionType)
	{
		case LED_REVERSE_CONNECTION:
		DIO_voidGetPinValue(copy_u8LedPort , copy_u8LedPin , DIO_PIN_HIGH);
		break;
		
		case LED_FORWARD_CONNECTION:
		DIO_voidGetPinValue(copy_u8LedPort , copy_u8LedPin , DIO_PIN_LOW);
		break;
	}
}

void LED_voidToggle  (u8 copy_u8LedPort ,u8 copy_u8LedPin)
{
	DIO_voidTogglePinValue(copy_u8LedPort , copy_u8LedPin);
}
