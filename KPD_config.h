/*
 * KPD_config.h
 *
 * Created: 2/8/2026 1:13:35 PM
 *  Author: hamza
 */ 


#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

/* Columns Pins */
#define KPD_COL_PORT   DIO_PORTD
#define KPD_ROW_PORT   DIO_PORTA

#define KPD_COL1_PIN   DIO_PIN2
#define KPD_COL2_PIN   DIO_PIN3
#define KPD_COL3_PIN   DIO_PIN7

#define KPD_ROW1_PIN   DIO_PIN1
#define KPD_ROW2_PIN   DIO_PIN2
#define KPD_ROW3_PIN   DIO_PIN3

extern u8 KPD_COL_PINS[3];
extern u8 KPD_ROW_PINS[3];

extern u8 KPD_KEYS[3][3];

#endif
