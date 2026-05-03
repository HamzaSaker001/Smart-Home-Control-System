/*
 * EXTI_program.c
 *
 * Created: 2/9/2026 1:35:12 PM
 *  Author: hamza
 */ 
 
/*UTILES_LIB*/
#include "STD_types.h"
#include "Bit_Math.h"

/*MCAL*/
#include "EXTI_interface.h"
#include "EXTI_register.h"

static void(*PVR_pToFunCallBack_INT0)(void);

void EXTI_voidInit(EXTI_intSrc_t copy_tIntSource, EXTI_SenseCtrl_t copy_tIntSenseCtrl)
{
	switch(copy_tIntSource)
	{
		case EXTI_INT0:
		switch(copy_tIntSenseCtrl)
		{
			case EXTI_FALLING_EDGE:
			CLR_BIT(MCUCR_REG, ISC00);
			SET_BIT(MCUCR_REG, ISC01);
			break;
			
			case EXTI_RISING_EDGE:
			SET_BIT(MCUCR_REG, ISC00);
			SET_BIT(MCUCR_REG, ISC01);
			break;
			
			case EXTI_LOW_LEVEL:
			CLR_BIT(MCUCR_REG, ISC00);
			CLR_BIT(MCUCR_REG, ISC01);
			break;
			
			case EXTI_ANY_LOGICAL_CHANGE:
			SET_BIT(MCUCR_REG, ISC00);
			CLR_BIT(MCUCR_REG, ISC01);
			break;
		}
		break;
		
		case EXTI_INT1:
		switch(copy_tIntSenseCtrl)
		{
			case EXTI_FALLING_EDGE:
			CLR_BIT(MCUCR_REG, ISC10);
			SET_BIT(MCUCR_REG, ISC11);
			break;
			
			case EXTI_RISING_EDGE:
			SET_BIT(MCUCR_REG, ISC10);
			SET_BIT(MCUCR_REG, ISC11);
			break;
			
			case EXTI_LOW_LEVEL:
			CLR_BIT(MCUCR_REG, ISC10);
			CLR_BIT(MCUCR_REG, ISC11);
			break;
			
			case EXTI_ANY_LOGICAL_CHANGE:
			SET_BIT(MCUCR_REG, ISC10);
			CLR_BIT(MCUCR_REG, ISC11);
			break;
		}
		break;
		
		case EXTI_INT2:
		switch(copy_tIntSenseCtrl)
		{
			case EXTI_FALLING_EDGE:
			CLR_BIT(MCUCSR_REG, ISC2);
			break;
			
			case EXTI_RISING_EDGE:
			SET_BIT(MCUCSR_REG, ISC2);
			break;
		}
		break;			
	}
}

void EXTI_voidEnable(EXTI_intSrc_t copy_tIntSource)
{
	switch(copy_tIntSource)
	{
		case EXTI_INT0:
		SET_BIT(GICR_REG, INTF0);
		break;
		
		case EXTI_INT1:
		SET_BIT(GICR_REG, INTF1);
		break;
		
		case EXTI_INT2:
		SET_BIT(GICR_REG, INTF2);
		break;
	}	
}

void EXTI_voidDisable(EXTI_intSrc_t copy_tIntSource)
{
	switch(copy_tIntSource)
	{
		case EXTI_INT0:
		CLR_BIT(GICR_REG, INTF0);
		break;
		
		case EXTI_INT1:
		CLR_BIT(GICR_REG, INTF1);
		break;
		
		case EXTI_INT2:
		CLR_BIT(GICR_REG, INTF2);
		break;
	}
}	

void EXTI_voidSetCallBackINT0 (void(*pToFunCallBack)(void))
{
	if (pToFunCallBack != NULL)
	{
		PVR_pToFunCallBack_INT0 = pToFunCallBack;
	} 
	else
	{
		//return error state
	}
}
	
 void __vector_1 (void) __attribute__((signal));
 void __vector_1 (void)
 {
	 if (PVR_pToFunCallBack_INT0 != NULL) 
	 {
		 PVR_pToFunCallBack_INT0();
	 } 
	 else
	 {
		 //return error state
	 }
 }
