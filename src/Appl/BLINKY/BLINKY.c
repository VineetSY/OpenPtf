/*************************************************************************************************
 * Module name: BLINKY.c
 *
 * Purpose:
 *
 * Created on: 18-Apr-2020
 *
 * Author: Vineet
 *************************************************************************************************/


/*************************************************************************************************
 *	Includes
 *************************************************************************************************/
#include "stm32l4xx.h"
#include "Types.h"
#include "GPIO.h"

/*************************************************************************************************
 *	MACRO
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
 *  @name - BLINKY_LED_Update
 *
 *  @summary - On_board and external LED toggle
 *
 *  @param - NA
 *
 *  @retval- NA
 *************************************************************************************************/
void BLINKY_LED_Update(void)
{
	static uint32 i;
	i++;
	//Turn OFF the LED at port PA5
	if(i > 1000)
	{
		i = 0;
		GPIO_PinMode_Update((uint8)GPIO_PA5, (uint8)MODE_LOW);
		GPIO_PinMode_Update((uint8)GPIO_PA6, (uint8)MODE_HIGH);
	}
	else if (i == 500)
	{
		GPIO_PinMode_Update((uint8)GPIO_PA5, (uint8)MODE_HIGH);
		GPIO_PinMode_Update((uint8)GPIO_PA6, (uint8)MODE_LOW);
	}
	else
	{
		//Do nothing
	}

	return;
}
