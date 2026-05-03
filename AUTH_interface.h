/*
 * AUTH_interface.h
 *
 * Created: 2/22/2026 10:09:41 PM
 *  Author: hamza
 */ 


#ifndef AUTH_INTERFACE_H_
#define AUTH_INTERFACE_H_

void AUTH_voidInit(void);
void AUTH_voidLogin(u8* pu8Username, u8* pu8Password, u8* pu8Role, u8* pu8Trials, u8* pu8UserCount);
void AUTH_voidAddUser(u8* pu8Username, u8* pu8Password, u8* pu8Role, u8* pu8UserCount);
void AUTH_voidDeleteUser(u8* pu8Username, u8* pu8Role);

#endif /* AUTH_INTERFACE_H_ */