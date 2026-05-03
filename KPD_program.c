/*
 * KPD_program.c
 *
 * Created: 2/8/2026 1:12:47 PM
 *  Author: hamza
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

/*UTILES_LIB*/
#include "Bit_Math.h"
#include "STD_types.h"

/*MCAL*/
#include "DIO_interface.h"

/*HAL*/
#include "KPD_config.h"
#include "KPD_interface.h"

u8 KPD_COL_PINS[3] = {KPD_COL1_PIN, KPD_COL2_PIN, KPD_COL3_PIN};
u8 KPD_ROW_PINS[3] = {KPD_ROW1_PIN, KPD_ROW2_PIN, KPD_ROW3_PIN};

/* Keypad Map */
u8 KPD_KEYS[3][3] =
{
	{'1','2','3'},
	{'4','5','6'},
	{'7','8','9'}
};


void KPD_voidInit(void)
{
	DIO_voidSetPinDirection(DIO_PORTD,KPD_COL1_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,KPD_COL2_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,KPD_COL3_PIN,DIO_PIN_OUTPUT);
	
	DIO_voidSetPinDirection(DIO_PORTA,KPD_ROW1_PIN,DIO_PIN_INPUT);
	DIO_voidSetPinDirection(DIO_PORTA,KPD_ROW2_PIN,DIO_PIN_INPUT);
	DIO_voidSetPinDirection(DIO_PORTA,KPD_ROW3_PIN,DIO_PIN_INPUT);
	
	// Deactivate all columns
	DIO_voidSetPinValue(DIO_PORTD, KPD_COL1_PIN, DIO_PIN_HIGH);
	DIO_voidSetPinValue(DIO_PORTD, KPD_COL2_PIN, DIO_PIN_HIGH);
	DIO_voidSetPinValue(DIO_PORTD, KPD_COL3_PIN, DIO_PIN_HIGH);
}

void KPD_voidGetValue(u8* pu8PressedVal)
{
	u8 Local_u8Col;
	u8 Local_u8Row;
	u8 Local_u8PinVal;

	/* Default value (No key pressed) */
	*pu8PressedVal = 0xFF;

	for(Local_u8Col = 0; Local_u8Col < 3; Local_u8Col++)
	{
		/* Activation: one column LOW */
		DIO_voidSetPinValue(KPD_COL_PORT, KPD_COL_PINS[Local_u8Col], DIO_PIN_LOW);

		for(Local_u8Row = 0; Local_u8Row < 3; Local_u8Row++)
		{
			DIO_voidGetPinValue(KPD_ROW_PORT, KPD_ROW_PINS[Local_u8Row], &Local_u8PinVal);

			if(Local_u8PinVal == DIO_PIN_LOW)
			{
				/* Debounce */
				_delay_ms(20);
				DIO_voidGetPinValue(KPD_ROW_PORT, KPD_ROW_PINS[Local_u8Row], &Local_u8PinVal);

				if(Local_u8PinVal == DIO_PIN_LOW)
				{
					/* Store pressed key using pointer */
					*pu8PressedVal = KPD_KEYS[Local_u8Row][Local_u8Col];

					/* Wait until release */
					while(Local_u8PinVal == DIO_PIN_LOW)
					{
						DIO_voidGetPinValue(KPD_ROW_PORT, KPD_ROW_PINS[Local_u8Row], &Local_u8PinVal);
					}

					/* Deactivation */
					DIO_voidSetPinValue(KPD_COL_PORT, KPD_COL_PINS[Local_u8Col], DIO_PIN_HIGH);
					return;
				}
			}
		}

		/* Deactivation: column HIGH */
		DIO_voidSetPinValue(KPD_COL_PORT, KPD_COL_PINS[Local_u8Col], DIO_PIN_HIGH);
	}
}
