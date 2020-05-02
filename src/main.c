/*************************************************************************************************
 * Module name: main.c
 *
 * Purpose: C program startup file.
 *
 * Created on: 02-May-2020
 *
 * Author: Vineet
 *************************************************************************************************/


/*************************************************************************************************
 *	Includes
 *************************************************************************************************/
#include "Cmn_Types.h"
#include "Project_Cfg.h"

/*MCU Specific Header File*/
#if (_MCU_STM32L476RG_ == ON)
# include "stm32l4xx.h"
#endif

#if ( _GPIO_MODULE_ == ON )
# include "GPIO.h"
#endif
#if ( _TIMER_MODULE_ == ON )
# include "TIMER.h"
#endif
#if ( _INTRPT_MODULE_ == ON )
# include "INTRPT.h"
#endif
#if ( _CLOCK_MODULE_ == ON )
# include "CLOCK.h"
#endif
#if ( _PRINT_MODULE_ == ON )
# include "PRINT.h"
#endif


/*************************************************************************************************
 *	MACRO & Types
 *************************************************************************************************/


/*************************************************************************************************
 *	Private variables
 *************************************************************************************************/


/*************************************************************************************************
 *	Global variables
 *************************************************************************************************/

/*************************************************************************************************
 *	Private function prototypes
 *************************************************************************************************/


/*************************************************************************************************
 *	Function Definitions
 *************************************************************************************************/


/*************************************************************************************************
 *  @name - main
 *
 *  @summary - standard c main function. This function is where the C program starts.
 *
 *  @param - 
 *
 *  @retval- 
 *************************************************************************************************/
int main(void)
{
	/**
	*  IMPORTANT NOTE!
	*  The symbol VECT_TAB_SRAM needs to be defined when building the project
	*  if code has been located to RAM and interrupts are used.
	*  Otherwise the interrupt table located in flash will be used.
	*  See also the <system_*.c> file and how the SystemInit() function updates
	*  SCB->VTOR register.
	*  E.g.  SCB->VTOR = 0x20000000;
	*/

	uint32 delay = 0;
	uint32 counter = 0;

	/* System Initialization */
	CLOCK_Init();
	GPIO_Init();

#if (_MCU_STM32L476RG_ == ON)
	SystemCoreClockUpdate();
#endif

	/* Infinite loop */
	while (1)
	{
		if(delay == 100000)
		{
			counter++;
			GPIO_UsrBtnB1_Update();
			PRINT_String("Print Count number ", counter);
			delay = 0;
			__WFI();
		}
		else
		{
			delay++;
		}

	}

	/*main function should never be returned/exited, if this is reached it is most likely an error*/
	return ERR;
}
