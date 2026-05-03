/*
 * Smart_Home_test.c
 *
 * Created: 2/22/2026 10:03:25 PM
 * Author : hamza
 */ 

/*UTILES Lib*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL Layer */
#include "DIO_interface.h"
#include "UART_interface.h"

/* APP Layer */
#include "APP_interface.h"

int main(void)
{
	/* 1. Initialize the Application */
	APP_voidInit();
	
	/* 2. Global Interrupt Enable (If using interrupts for UART/Timer) */
	// SET_BIT(SREG_REG, 7); 

	/* 3. Run the System 
	   This loop handles the login state machine and hardware control */
	APP_voidRun();
	
	while(1)
	{
	}
	return 0; 
}