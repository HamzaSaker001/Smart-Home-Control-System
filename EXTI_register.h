/*
 * EXTI_register.h
 *
 * Created: 2/9/2026 1:36:30 PM
 *  Author: hamza
 */ 


#ifndef EXTI_REGISTER_H_
#define EXTI_REGISTER_H_

#define  MCUCR_REG     (*(volatile u8*)0x55)

#define  ISC11         3
#define  ISC10 		   2
#define  ISC01 		   1
#define  ISC00		   0

#define  MCUCSR_REG    (*(volatile u8*)0x54)

#define  ISC2          6

#define  GICR_REG      (*(volatile u8*)0x5B)

#define  INTF1         7
#define  INTF0		   6
#define  INTF2		   5

#define  GIFR_REG      (*(volatile u8*)0x5A)

#define  INTF1         7 
#define  INTF0		   6
#define  INTF2		   5

#endif /* EXTI_REGISTER_H_ */