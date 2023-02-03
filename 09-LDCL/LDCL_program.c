/***************************************/
/* Author  :Gomaa                      */
/* Date    :19 Nov 2020                */
/* Version :V01                        */
/***************************************/

#include  "STD_TYPES.h"
#include  "BIT_MATH.h"

#include "GPIO_interface.h"
#include "STK_interface.h"
#include "RCC_interface.h"

#include  "LDCL_interface.h"
#include  "LDCL_private.h"
#include  "LDCL_config.h"

void LDCL_voidInit(void)
{
	STK_voidInit();
	/* Enable Clock For GPIOA Periphiral */
	RCC_voidEnableClock(RCC_APB2,RCC_IOPA);
	
	/* Set Clock Pin To be Output */
	GPIO_voidSetPinDirection(LDCL_CLCK,GPIO_OUTPUT_10MHZ_PP);
	/* Set Data pin to be input */
	GPIO_voidSetPinDirection(LDCL_DATA,GPIO_INPUT_FLOATING);
	/* set Clock Polarity to be Negative  */
	GPIO_voidSetPinValue(LDCL_CLCK,GPIO_LOW);
	
}

u32 LDCL_u32ReadData(void)
{
u32 Locale_Data = 0;
u8  Locale_Bit = 0;
u8 i = 23;
   /* wait until The data pin to be low */
	while(GPIO_voidGetPinValue(LDCL_DATA)==1);
   for( i= 23 ;i > 0;--i)
        {   
	        /* make the needed pulses and get the data */
			GPIO_voidSetPinValue(LDCL_CLCK,GPIO_HIGH);
			STK_voidSetBusyWait(2);
			Locale_Bit = GPIO_voidGetPinValue(LDCL_DATA);
			GPIO_voidSetPinValue(LDCL_CLCK,GPIO_LOW);
			STK_voidSetBusyWait(2);
			//(Locale_Bit == 1)?SET_BIT(Locale_Data,i):CLR_BIT(Locale_Data,i);
			if(Locale_Bit == 1)
			{
				SET_BIT(Locale_Data,i);
			}
			else{
				CLR_BIT(Locale_Data,i);
			}
			
	     
        }
            GPIO_voidSetPinValue(LDCL_CLCK,GPIO_HIGH);
   			STK_voidSetBusyWait(2);
            Locale_Bit = GPIO_voidGetPinValue(LDCL_DATA);
            GPIO_voidSetPinValue(LDCL_CLCK,GPIO_LOW);
            STK_voidSetBusyWait(2);

         if(Locale_Bit == 1)
         			{
         				SET_BIT(Locale_Data,i);
         			}
         			else{
         				CLR_BIT(Locale_Data,i);
         			}

		/* make The pulse Num 25 or 26 or 27 **/
		    #if   LDCL_GAIN == LDCL_128
		    GPIO_voidSetPinValue(LDCL_CLCK,GPIO_HIGH);
			STK_voidSetBusyWait(2);
			GPIO_voidSetPinValue(LDCL_CLCK,GPIO_LOW);
			STK_voidSetBusyWait(2);
			#elif    LDCL_GAIN == LDCL_32
			GPIO_voidSetPinValue(LDCL_CLCK,GPIO_HIGH);
			STK_voidSetBusyWait(1000);
			GPIO_voidSetPinValue(LDCL_CLCK,GPIO_LOW);
			STK_voidSetBusyWait(1000);
			GPIO_voidSetPinValue(LDCL_CLCK,GPIO_HIGH);
			STK_voidSetBusyWait(1000);
			GPIO_voidSetPinValue(LDCL_CLCK,GPIO_LOW);
			STK_voidSetBusyWait(1000);
			#elif   LDCL_GAIN==LDCL_64
			GPIO_voidSetPinValue(LDCL_CLCK,GPIO_HIGH);
			STK_voidSetBusyWait(1000);
			GPIO_voidSetPinValue(LDCL_CLCK,GPIO_LOW);
			STK_voidSetBusyWait(1000);GPIO_voidSetPinValue(LDCL_CLCK,GPIO_HIGH);
			STK_voidSetBusyWait(1000);
			GPIO_voidSetPinValue(LDCL_CLCK,GPIO_LOW);
			STK_voidSetBusyWait(1000);GPIO_voidSetPinValue(LDCL_CLCK,GPIO_HIGH);
			STK_voidSetBusyWait(1000);
			GPIO_voidSetPinValue(LDCL_CLCK,GPIO_LOW);
			STK_voidSetBusyWait(1000);
			#endif

		Locale_Data =~(Locale_Data);
		Locale_Data = Locale_Data + 1;
		Locale_Data &=~(0b11111111<<24);


  return ((Locale_Data-167532));
}
