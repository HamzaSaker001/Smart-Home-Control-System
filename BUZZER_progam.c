/*
 * BUZZER_progam.c
 *
 * Created: 11/24/2025 1:57:28 PM
 *  Author: hamza
 */ 

/*UTILES Lib*/
#include "STD_types.h"
#include "Bit_Math.h"

/*MCAL*/
#include "DIO_interface.h"

/*MAL*/
#include "BUZZER_interface.h"

void BUZZER_voidInit  (u8 copy_u8BUZZERPort ,u8 copy_u8BUZZERPin)
{
	DIO_voidSetPinDirection(copy_u8BUZZERPort , copy_u8BUZZERPin , DIO_PIN_OUTPUT);
}

void BUZZER_voidOn    (u8 copy_u8BUZZERPort ,u8 copy_u8BUZZERPin)
{
	DIO_voidSetPinValue(copy_u8BUZZERPort , copy_u8BUZZERPin, DIO_PIN_HIGH);
}

void BUZZER_voidOff   (u8 copy_u8BUZZERPort ,u8 copy_u8BUZZERPin)
{
	DIO_voidSetPinValue(copy_u8BUZZERPort , copy_u8BUZZERPin, DIO_PIN_LOW);	
}

void BUZZER_voidToggle  (u8 copy_u8BUZZERPort ,u8 copy_u8BUZZERPin)
{
	DIO_voidTogglePinValue(copy_u8BUZZERPort , copy_u8BUZZERPin);
}
