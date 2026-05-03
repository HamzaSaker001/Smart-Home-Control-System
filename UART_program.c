/*
 * UART_program.c
 *
 * Created: 2/19/2026 12:08:32 AM
 *  Author: hamza
 */ 

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "UART_interface.h"
#include "UART_register.h"


void UART_voidInit(void)
{
	/* Set Buad Rate = 9600 (f(osc) = 16MHZ, Double speed off) */
	CLR_BIT(UCSRA_REG, U2X);
	UBRRL_REG = 103;
	
	/* Disable UART Interrupts */
	CLR_BIT(UCSRB_REG, RXCIE);
	CLR_BIT(UCSRB_REG, TXCIE);
	CLR_BIT(UCSRB_REG, UDRIE);
	
	/* writing on UCSRC , select UART MODE = Asynchronous , configure no parity , configure stop bits = 1 , configure data bits = 8 , configure no polarity */
	UCSRC_REG = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	CLR_BIT(UCSRB_REG, UCSZ2);
	
	/* Enable UART Rx */
	SET_BIT(UCSRB_REG, RXEN);
	
	/* Enable UART Tx */
	SET_BIT(UCSRB_REG, TXEN);
}

void UART_voidTxChar(u8 copy_u8TxData)
{
	/* Busy wait for UART Data Reg. Empty flag */
	while(0 == GET_BIT(UCSRA_REG, UDRE));
	
	UDR_REG = copy_u8TxData;
}


void UART_voidRxChar(u8* pu8RxData)
{
	if(pu8RxData != NULL)
	{
		/* Busy wait for UART Rx Complete flag */
		while(0 == GET_BIT(UCSRA_REG, RXC));
		
		*pu8RxData = UDR_REG;
	}
	else
	{
		//return Error State
	}
}

void UART_voidTxString(u8* pu8TxString)
{
	if(pu8TxString != NULL)
	{
		u8 local_u8Counter = 0;
		
		while(pu8TxString[local_u8Counter] != '\0')
		{
			UART_voidTxChar(pu8TxString[local_u8Counter]);
			local_u8Counter++;
		}
	}
	else
	{
		// return Error State
	}
}

void UART_voidRxString(u8* pu8RxString)
{
	if(pu8RxString != NULL)
	{
		u8 local_u8Counter = 0;
		
		do
		{
			UART_voidRxChar(&pu8RxString[local_u8Counter]);
			local_u8Counter++;
		} while (pu8RxString[local_u8Counter-1] != '\r');
		
		pu8RxString[local_u8Counter-1] = '\0';
	}
	else
	{
		// return Error State
	}
}

