/*
 * AUTH_program.c
 *
 * Created: 2/22/2026 10:09:20 PM
 *  Author: hamza
 */ 

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "I2C_interface.h"

/* HAL */
#include "EEPROM_interface.h"

/* Service */
#include "AUTH_config.h"
#include "AUTH_interface.h"

// Hardcoded Admin
u8 AdminUser[AUTH_USERNAME_LEN] = "admin";
u8 AdminPass[AUTH_PASSWORD_LEN] = "1234";

// Utility function to get EEPROM address via pointer
static void GetUserAddress(u8 Copy_u8Index, u16* pu16Addr)
{
	// Start users AFTER the space theoretically reserved for admin
	*pu16Addr = AUTH_EEPROM_START + 0x10 + (Copy_u8Index * (AUTH_USERNAME_LEN + AUTH_PASSWORD_LEN));
}

// Compare Arrays via pointer logic
static void CompareArrays(u8* pu8Arr1, u8* pu8Arr2, u8 Copy_u8Len, u8* pu8Result)
{
	*pu8Result = 1; // Assume Match
	for(u8 i = 0; i < Copy_u8Len; i++) {
		if(pu8Arr1[i] != pu8Arr2[i]) {
			*pu8Result = 0; // Match Failed
			break;
		}
	}
}

void AUTH_voidInit(void)
{
	EEPROM_voidInit();
}

void AUTH_voidLogin(u8* pu8Username, u8* pu8Password, u8* pu8Role, u8* pu8Trials, u8* pu8UserCount)
{
	u8 Local_u8UserMatch = 0;
	u8 Local_u8PassMatch = 0;
	
	*pu8Role = AUTH_NOT_LOGGED; // Default state

	// 1. Check Admin
	CompareArrays(pu8Username, AdminUser, AUTH_USERNAME_LEN, &Local_u8UserMatch);
	CompareArrays(pu8Password, AdminPass, AUTH_PASSWORD_LEN, &Local_u8PassMatch);
	
	if(Local_u8UserMatch == 1 && Local_u8PassMatch == 1) {
		*pu8Role = AUTH_ADMIN_ROLE;
		*pu8Trials = 0;
	}
	else {
		// 2. Check Users in EEPROM
		u16 Local_u16Addr = 0;
		u8 Local_u8StoredUser[AUTH_USERNAME_LEN];
		u8 Local_u8StoredPass[AUTH_PASSWORD_LEN];
		
		for(u8 i = 0; i < *pu8UserCount; i++) {
			GetUserAddress(i, &Local_u16Addr);
			EEPROM_voidReadPage(Local_u16Addr, Local_u8StoredUser, AUTH_USERNAME_LEN);
			EEPROM_voidReadPage(Local_u16Addr + AUTH_USERNAME_LEN, Local_u8StoredPass, AUTH_PASSWORD_LEN);
			
			CompareArrays(pu8Username, Local_u8StoredUser, AUTH_USERNAME_LEN, &Local_u8UserMatch);
			CompareArrays(pu8Password, Local_u8StoredPass, AUTH_PASSWORD_LEN, &Local_u8PassMatch);
			
			if(Local_u8UserMatch == 1 && Local_u8PassMatch == 1) {
				*pu8Role = AUTH_USER_ROLE;
				*pu8Trials = 0;
				break;
			}
		}
	}

	// 3. Handle Failures
	if(*pu8Role == AUTH_NOT_LOGGED) {
		(*pu8Trials)++;
		if(*pu8Trials >= 3) {
			*pu8Role = AUTH_BLOCKED;
		}
	}
}

void AUTH_voidAddUser(u8* pu8Username, u8* pu8Password, u8* pu8Role, u8* pu8UserCount)
{
	if(*pu8Role == AUTH_ADMIN_ROLE && *pu8UserCount < AUTH_MAX_USERS) {
		u16 Local_u16Addr;
		GetUserAddress(*pu8UserCount, &Local_u16Addr);
		
		EEPROM_voidWritePage(Local_u16Addr, pu8Username, AUTH_USERNAME_LEN);
		EEPROM_voidWritePage(Local_u16Addr + AUTH_USERNAME_LEN, pu8Password, AUTH_PASSWORD_LEN);
		
		(*pu8UserCount)++;
	}
}

void AUTH_voidDeleteUser(u8* pu8Username, u8* pu8Role)
{
	if(*pu8Role == AUTH_ADMIN_ROLE) {
		u16 Local_u16Addr;
		u8 Local_u8StoredUser[AUTH_USERNAME_LEN];
		u8 Local_u8Match = 0;
		u8 Local_u8Empty[AUTH_USERNAME_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

		for(u8 i = 0; i < AUTH_MAX_USERS; i++) {
			GetUserAddress(i, &Local_u16Addr);
			EEPROM_voidReadPage(Local_u16Addr, Local_u8StoredUser, AUTH_USERNAME_LEN);
			
			CompareArrays(pu8Username, Local_u8StoredUser, AUTH_USERNAME_LEN, &Local_u8Match);
			
			if(Local_u8Match == 1) {
				EEPROM_voidWritePage(Local_u16Addr, Local_u8Empty, AUTH_USERNAME_LEN);
				break; // Found and deleted
			}
		}
	}
}