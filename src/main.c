/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2019-05-03

The MIT License (MIT)
Copyright (c) 2019 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32l4xx.h"
#include "Types.h"
#include "GPIO.h"
#include "TIMER.h"


/* Private macro */

/* Private variables */

uint8 VAR_TIM2_IRQHandler 				= FALSE;

/* Private function prototypes */

void LameTask1(void);
void LameTask2(void);

/* Private functions */

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
	unsigned long int i = 0;

	/**
	*  IMPORTANT NOTE!
	*  The symbol VECT_TAB_SRAM needs to be defined when building the project
	*  if code has been located to RAM and interrupts are used.
	*  Otherwise the interrupt table located in flash will be used.
	*  See also the <system_*.c> file and how the SystemInit() function updates
	*  SCB->VTOR register.
	*  E.g.  SCB->VTOR = 0x20000000;
	*/

	/* TODO - Add your application code here */
	IOPortInit();
	ReloadTimerInit();
	/* Infinite loop */

	while (1)
	{


	}
}

void LameTask1(void)
{
	//Boring Task 1 turns off On board led and turns on external led
	GPIOA ->BRR |= (GPIO_BRR_BR5);
	GPIOA ->BSRR |= (GPIO_BSRR_BS6);
}

void LameTask2(void)
{
	//Boring Task 2 turns On On board led and turns off external led
	GPIOA ->BSRR |= (GPIO_BSRR_BS5);
	GPIOA ->BRR |= (GPIO_BRR_BR6);
}

