/*
 * INIT.c
 *
 *  Created on: 05-Apr-2020
 *      Author: Vineet
 */


/* Includes */
#include "stm32l4xx.h"
#include "Types.h"
#include "GPIO.h"


/* Private macro */


/* Private variables */

/* Private function prototypes */

/* Private functions */

/**************************************************************************************************
 *  @name - IOPortInit
 *
 *  @summary - Generic function to initialize the GPIO pins
 *
 *  @param - NA
 *
 *  @retval- NA
 **************************************************************************************************/
void IOPortInit(void)
{

	/*Reset and clock control - Advanced high performance bus- Enabling GPIO Port A*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	//Setup control registers for the LED output
	//Mode Register for output
	GPIOA ->MODER |= (GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0);
	GPIOA ->MODER &= ~(GPIO_MODER_MODE5_1 | GPIO_MODER_MODE6_1);

	//Output type register (push pull)
	GPIOA ->OTYPER &= ~(GPIO_OTYPER_OT5 | GPIO_OTYPER_OT6);

	//SPEED Register (High speed)
	GPIOA ->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_0 | GPIO_OSPEEDR_OSPEED5_1 | GPIO_OSPEEDR_OSPEED6_0 | GPIO_OSPEEDR_OSPEED6_1;

	//Pull up pull down register
	GPIOA ->PUPDR &= ~(GPIO_PUPDR_PUPD5 | GPIO_PUPDR_PUPD6);

	//Bit set reset register
	//Turn ON the LED at PA5 and PA6
	GPIOA ->BSRR |= (GPIO_BSRR_BS5 | GPIO_BSRR_BS6); //set pin 5,6 on port A


	return;
}


/**************************************************************************************************
 *  @name - IOPinMode
 *
 *  @summary - GPIO pin digital output mode update
 *
 *  @param in - Pin: GPIO pin number to select
 *
 *  @param in - Mode: output mode for the selected pin
 *
 *  @retval- NA
 **************************************************************************************************/
void IOPinMode(uint8 Pin, uint8 Mode)
{
	switch(Mode)
	{
		case MODE_LOW:
			GPIOA ->BRR |= (GPIO_BRR_BR5);
			GPIOA ->BRR |= (GPIO_BRR_BR6);
			break;

		case MODE_HIGH:
			GPIOA ->BSRR |= (GPIO_BSRR_BS6);
			GPIOA ->BSRR |= (GPIO_BSRR_BS5);
			break;

		default:
			break;
	}
}
