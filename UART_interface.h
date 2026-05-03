/*
 * UART_interface.h
 *
 * Created: 2/19/2026 12:11:02 AM
 *  Author: hamza
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


/******************* APIs Prototypes *******************/

void UART_voidInit(void);
void UART_voidTxChar(u8 copy_u8TxData);
void UART_voidRxChar(u8* pu8RxData);
void UART_voidTxString(u8* pu8TxString);
void UART_voidRxString(u8* pu8RxString);



#endif /* UART_INTERFACE_H_ */