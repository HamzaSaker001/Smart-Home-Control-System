/*
 * MANG_program.c
 *
 * Created: 2/22/2026 10:11:18 PM
 *  Author: hamza
 */ 

/*UTILES Lib*/
#include "STD_types.h"
#include "Bit_Math.h"

/*MCAL*/
#include "PWM1_interface.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "PWM0_interface.h"

/*HAL*/
#include "SRVM_interface.h"
#include "LED_inteface.h"
#include "LCD_interface.h"
#include "DCM_interface.h"
#include "DCM_config.h"
#include "KPD_interface.h"
#include "LM35_interface.h"

/* Service */
#include "MANG_config.h"
#include "MANG_interface.h"

typedef struct {
	u8 Leds[5];
	u8 AC;
	u8 Door;
} MANG_State_t;

static MANG_State_t SystemHardware = {{0}, MANG_AC_OFF, MANG_DOOR_CLOSE};

void MANG_voidInit(void)
{
	SRVM_voidInit();
	
	for(u8 i=0; i<5; i++) { 
		LED_voidInit(DIO_PORTC, DIO_PIN2 + i);[cite: 1]
	}
	
	LED_voidInit(DIO_PORTD, DIO_PIN7);[cite: 1]
	
	DCM_voidInit(DCM_MOTOR_A);[cite: 1]
	PWM0_voidInit();[cite: 1]
	PWM1_voidInitChannel1A();[cite: 1]
	LM35_voidInit();[cite: 1]
}

void MANG_voidLedControl(u8 Copy_u8LampID, u8 Copy_u8State)
{
	if(Copy_u8LampID >= 1 && Copy_u8LampID <= 5)
	{
		u8 Pin = DIO_PIN2 + (Copy_u8LampID - 1);[cite: 1]
		
		if(Copy_u8State == MANG_LED_ON) { 
			LED_voidOn(DIO_PORTC, Pin, LED_FORWARD_CONNECTION);[cite: 1]
		}
		else { 
			LED_voidOff(DIO_PORTC, Pin, LED_FORWARD_CONNECTION);[cite: 1]
		}
		SystemHardware.Leds[Copy_u8LampID - 1] = Copy_u8State;[cite: 1]
	}
}

void MANG_voidDimmerControl(u8 Copy_u8Level)
{
	PWM0_voidGenrate(Copy_u8Level);[cite: 1]
}

void MANG_voidACCtrl(void)
{
	u8 Local_u8Temp;
	LM35_voidGetTemperature(&Local_u8Temp);[cite: 1]

	if(Local_u8Temp >= 28 && SystemHardware.AC == MANG_AC_OFF) {
		DCM_voidOn(DCM_MOTOR_A, DCM_CW);[cite: 1]
		SystemHardware.AC = MANG_AC_ON;[cite: 1]
	}
	else if(Local_u8Temp <= 21 && SystemHardware.AC == MANG_AC_ON) {
		DCM_voidOff(DCM_MOTOR_A);[cite: 1]
		SystemHardware.AC = MANG_AC_OFF;[cite: 1]
	}
}

void MANG_voidDoorCtrl(u8 Copy_u8State)
{
	if(Copy_u8State == MANG_DOOR_OPEN) { 
		SRVM_voidOn(90);[cite: 1]
	}
	else { 
		SRVM_voidOn(0);[cite: 1]
	}
	SystemHardware.Door = Copy_u8State;[cite: 1]
}

void MANG_voidGetLedStatus(u8 Copy_u8LampID, u8* pu8Status)
{
	if(Copy_u8LampID >= 1 && Copy_u8LampID <= 5) { 
		*pu8Status = SystemHardware.Leds[Copy_u8LampID - 1];[cite: 1]
	}
}

void MANG_voidGetACStatus(u8* pu8ACStatus) 
{ 
	*pu8ACStatus = SystemHardware.AC;[cite: 1]
}

void MANG_voidGetDoorStatus(u8* pu8DoorStatus) 
{ 
	*pu8DoorStatus = SystemHardware.Door;[cite: 1]
}