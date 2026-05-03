/*
 * ALARM_program.c
 *
 * Created: 2/22/2026 10:11:39 PM
 *  Author: hamza
 */ 

/*UTILES Lib*/
#include "STD_types.h"
#include "Bit_Math.h"

/*MCAL*/
#include "DIO_interface.h"

/*MAL*/
#include "BUZZER_interface.h"

/* Service */
#include "ALARM_config.h"
#include "ALARM_interface.h"

void ALARM_voidInit(void)
{
	BUZZER_voidInit(ALARM_PORT, ALARM_PIN);
}

void ALARM_voidOn(void)
{
	BUZZER_voidOn(ALARM_PORT, ALARM_PIN);
}

void ALARM_voidOff(void)
{
	BUZZER_voidOff(ALARM_PORT, ALARM_PIN);
}