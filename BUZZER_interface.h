/*
 * BUZZER_interface.h
 *
 * Created: 11/24/2025 1:57:49 PM
 *  Author: hamza
 */ 


#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_

      /*****************************************************ABIs Prototypes************************************************/
	  
void BUZZER_voidInit  (u8 copy_u8BUZZERPort ,u8 copy_u8BUZZERPin);
void BUZZER_voidOn    (u8 copy_u8BUZZERPort ,u8 copy_u8BUZZERPin);
void BUZZER_voidOff   (u8 copy_u8BUZZERPort ,u8 copy_u8BUZZERPine);
void BUZZER_voidToggle  (u8 copy_u8BUZZERPort ,u8 copy_u8BUZZERPin);

#endif /* BUZZER_INTERFACE_H_ */