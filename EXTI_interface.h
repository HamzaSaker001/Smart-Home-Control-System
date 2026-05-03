/*
 * EXTI_interface.h
 *
 * Created: 2/9/2026 1:35:33 PM
 *  Author: hamza
 */ 


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

/*enum values for interrupt source*/

typedef enum
{
	EXTI_INT0,
	EXTI_INT1,
	EXTI_INT2
}EXTI_intSrc_t; 

/*enum values for interrupt trigger edge*/

typedef enum
{
	EXTI_RISING_EDGE,
	EXTI_FALLING_EDGE,
	EXTI_LOW_LEVEL,
	EXTI_ANY_LOGICAL_CHANGE
}EXTI_SenseCtrl_t;

/*****************************************APIs prototypes*****************************************/

void EXTI_voidInit(EXTI_intSrc_t copy_tIntSource, EXTI_SenseCtrl_t copy_tIntSenseCtrl);
void EXTI_voidEnable(EXTI_intSrc_t copy_tIntSource);
void EXTI_voidDisable(EXTI_intSrc_t copy_tIntSource);
void EXTI_voidSetCallBackINT0 (void(*pToFunCallBack)(void));

#endif /* EXTI_INTERFACE_H_ */