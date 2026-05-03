/*
 * APP_program.c
 *
 * Created: 2/22/2026 10:07:52 PM
 *  Author: hamza
 */ 

/*UTILES Lib*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*MCAL*/
#include "UART_interface.h"

/*MAL*/
#include "LCD_interface.h"
#include "KPD_interface.h"

/* Service */
#include "MANG_interface.h"
#include "MANG_config.h"
#include "AUTH_interface.h"
#include "AUTH_config.h"
#include "ALARM_interface.h"

/* APP */
#include "APP_interface.h"
#include "APP_config.h"

void APP_voidInit(void)
{
	UART_voidInit();
	MANG_voidInit();
	AUTH_voidInit();
	ALARM_voidInit();
	LCD_voidClear();
	LCD_voidDisplayString((u8*)"Smart Home Ready");
}

void APP_voidRun(void)
{
	// NO GLOBALS OR STATICS! All state managed here and passed by reference.
	u8 Local_u8CurrentRole = AUTH_NOT_LOGGED;
	u8 Local_u8Trials = 0;
	u8 Local_u8UserCount = 0; // In a real system, you'd read this from EEPROM on boot
	
	u8 Local_u8Username[AUTH_USERNAME_LEN + 1];
	u8 Local_u8Password[AUTH_PASSWORD_LEN + 1];
	u8 Local_u8MenuChoice = 0;

	while(1)
	{
		// Continuous automated functions
		MANG_voidACCtrl();

		if(Local_u8CurrentRole == AUTH_NOT_LOGGED)
		{
			UART_voidTxString((u8*)"\r\n--- Login ---");
			UART_voidTxString((u8*)"\r\nUser: ");
			UART_voidRxString(Local_u8Username);
			
			UART_voidTxString((u8*)"\r\nPass: ");
			UART_voidRxString(Local_u8Password);
			
			AUTH_voidLogin(Local_u8Username, Local_u8Password, &Local_u8CurrentRole, &Local_u8Trials, &Local_u8UserCount);
			
			if(Local_u8CurrentRole == AUTH_BLOCKED)
			{
				ALARM_voidOn();
				LCD_voidClear();
				LCD_voidDisplayString((u8*)"SYSTEM LOCKED!");
				UART_voidTxString((u8*)"\r\nALARM TRIGGERED! HW Reset Required.\r\n");
				while(1); // Dead end until hardware reset
			}
		}
		else if(Local_u8CurrentRole == AUTH_ADMIN_ROLE)
		{
			UART_voidTxString((u8*)"\r\n--- Admin Menu ---\r\n1. Control Home\r\n2. Add User\r\n3. Del User\r\nSelect: ");
			UART_voidRxChar(&Local_u8MenuChoice);
			
			if(Local_u8MenuChoice == '2') {
				UART_voidTxString((u8*)"\r\nNew User: ");
				UART_voidRxString(Local_u8Username);
				UART_voidTxString((u8*)"\r\nNew Pass: ");
				UART_voidRxString(Local_u8Password);
				AUTH_voidAddUser(Local_u8Username, Local_u8Password, &Local_u8CurrentRole, &Local_u8UserCount);
				UART_voidTxString((u8*)"\r\nUser Added.\r\n");
			}
			else if(Local_u8MenuChoice == '3') {
				UART_voidTxString((u8*)"\r\nUser to Del: ");
				UART_voidRxString(Local_u8Username);
				AUTH_voidDeleteUser(Local_u8Username, &Local_u8CurrentRole);
				UART_voidTxString((u8*)"\r\nUser Deleted.\r\n");
			}
			else if(Local_u8MenuChoice == '1') {
				// Here you would call your specific UART control logic for lights/doors
				UART_voidTxString((u8*)"\r\n[Door Opened]");
				MANG_voidDoorCtrl(MANG_DOOR_OPEN);
			}
		}
		else if(Local_u8CurrentRole == AUTH_USER_ROLE)
		{
			UART_voidTxString((u8*)"\r\n--- User Menu ---\r\n1. Control Lights\r\nSelect: ");
			UART_voidRxChar(&Local_u8MenuChoice);
			
			if(Local_u8MenuChoice == '1') {
				UART_voidTxString((u8*)"\r\n[Lamp 1 Toggled]");
				MANG_voidLedControl(1, MANG_LED_ON);
				// Add extended logic to turn off, use dimmer, etc.
			}
			// Notice: No door control for User Role
		}
	}
}