/*
 * MANG_interface.h
 *
 * Created: 2/22/2026 10:10:59 PM
 *  Author: hamza
 */ 


#ifndef MANG_INTERFACE_H_
#define MANG_INTERFACE_H_

void MANG_voidInit(void);
void MANG_voidLedControl(u8 Copy_u8LampID, u8 Copy_u8State);
void MANG_voidDimmerControl(u8 Copy_u8Level);
void MANG_voidACCtrl(void);
void MANG_voidDoorCtrl(u8 Copy_u8State);

void MANG_voidGetLedStatus(u8 Copy_u8LampID, u8* pu8Status);
void MANG_voidGetACStatus(u8* pu8ACStatus);
void MANG_voidGetDoorStatus(u8* pu8DoorStatus);


#endif /* MANG_INTERFACE_H_ */