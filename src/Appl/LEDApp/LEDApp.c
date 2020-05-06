/*************************************************************************************************
 * Module name: LEDApp.c
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
#include "Cmn_Types.h"
#include "Project_Cfg.h"
#if ( _GPIO_MODULE_ == ON )
# include "GPIO.h"
#endif
/*************************************************************************************************
 *	MACRO
 *************************************************************************************************/


/*************************************************************************************************
 *	Private variables
 *************************************************************************************************/
uint8 mode = 0;
GPIO_BtnState_e btnState = BtnNotPressed;

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
 *  @name - LEDApp_LED_Update
 *
 *  @summary - On_board and external LED toggle
 *
 *  @param - NA
 *
 *  @retval- NA
 *************************************************************************************************/
void LEDApp_LED_Update(void)
{
	static uint32 i;


	i++;
	btnState = GPIO_BtnB1State_Get();

	if(btnState == BtnPressed)
	{
		mode = 1;
	}
	//Turn OFF the LED at port PA5
	if(mode == 0)
	{
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
	}
	else
	{
		if(i > 1000)
		{
			i = 0;
			GPIO_PinMode_Update((uint8)GPIO_PA5, (uint8)MODE_HIGH);
			GPIO_PinMode_Update((uint8)GPIO_PA6, (uint8)MODE_HIGH);
		}
		else if (i == 500)
		{
			GPIO_PinMode_Update((uint8)GPIO_PA5, (uint8)MODE_LOW);
			GPIO_PinMode_Update((uint8)GPIO_PA6, (uint8)MODE_LOW);
		}
		else
		{
			//Do nothing
		}
	}

	return;
}


void LEDApp_BreatheLED_Update(void)
{
	static uint32 tick;
	static uint8 offset = (uint8)50;
	static uint32 pwmVal = (uint32)999;
	static uint8 dir = 0;

	if(tick == (uint32)100)
	{
		if((dir == 0))
		{
			pwmVal -= offset;
			GPIO_Pwm_Config(pwmVal);
			if(pwmVal == (uint32)49)
			{dir = 1;}
		}
		else
		{
			pwmVal += offset;
			GPIO_Pwm_Config(pwmVal);
			if(pwmVal == (uint32)999)
			{dir = 0;}
		}

		tick = 0;
	}
	tick++;
}