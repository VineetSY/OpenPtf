/*************************************************************************************************
 * Module name: PRINT.c
 *
 * Purpose:This module provides print functionality to output messages, with a very minimal memory
 * 			cost. This module can be mapped to use built-in ITM, or external LCD or UART.
 *
 * Created on: 24-Apr-2020
 *
 * Author: Vineet
 *************************************************************************************************/

#if ( _PRINT_MODULE_ == ON )
/*************************************************************************************************
 *	Includes
 *************************************************************************************************/
#include "Cmn_Types.h"
#include "Project_Cfg.h"
/*MCU Specific Header File*/
#if (_MCU_STM32L476RG_ == ON)
# include "stm32l4xx.h"
#endif

#include "PRINT.h"

/*************************************************************************************************
 *	MACRO & Types
 *************************************************************************************************/
#define NULL ((void *)0u)

#if ((_MCU_STM32L476RG_ == ON) && (_CORTEX_M4_CMSIS_ == ON))
# define SEND_CHAR_TO_DEVICE(x) ITM_SendChar(x)
#else
# define SEND_CHAR_TO_DEVICE(x)
#endif
/*************************************************************************************************
 *	Private variables
 *************************************************************************************************/


/*************************************************************************************************
 *	Global variables
 *************************************************************************************************/

/*************************************************************************************************
 *	Private function prototypes
 *************************************************************************************************/
static char* Local_itoa(uint32 num, char* str, uint32 base);
static void reverse(char str[], uint32 length);


/*************************************************************************************************
 *	Function Definitions
 *************************************************************************************************/


/*************************************************************************************************
 *  @name - PRINT_String
 *
 *  @summary - Prints character strings to configured output display method(serial wire out, LCD,
 *  			etc) and adds a new line character at the end of the string.
 *
 *  @param [in] - str: Character string to be printed
 *  @param [in] - InsertNewline: This parameter specified whether a Newline should 0be inserted,
 *  								following values are possible.
 *						@arg - NO_NEWLINE when specified the function will not add newline.
 *						@arg - ADD_NEWLINE when specified the function will add newline at the end.
 *
 *  @retval- StrLen: Returns length of Output string, new line character is not counted
 *************************************************************************************************/
uint8 PRINT_String(char *str, boolean InsertNewline)
{
	uint8 StrLen = 0; /*String length*/

	while(*str != (uint32)NULL)
	{
		(void)SEND_CHAR_TO_DEVICE(*str++);
		++StrLen;
	}

	if(InsertNewline == ADD_NEWLINE)
	{
		(void)SEND_CHAR_TO_DEVICE('\n');
	}

	return StrLen;
}


/*************************************************************************************************
 *  @name - PRINT_Number
 *
 *  @summary - Converts the given number to a string then prints character strings to configured
 *  			output display method(serial wire out, LCD,	etc) and adds a new line character at
 *  			the end of the string.
 *
 *  @param [in] - num: numerical value to be printed, treated as a base 10 for converting to string
 *  					before printing.
 *  @param [in] - InsertNewline: This parameter specified whether a Newline should 0be inserted,
 *  								following values are possible.
 *						@arg - NO_NEWLINE when specified the function will not add newline.
 *						@arg - ADD_NEWLINE when specified the function will add newline at the end.
 *
 *  @retval- StrLen: Returns length of Output string, new line character is not counted
 *************************************************************************************************/
void PRINT_Number(uint32 num, boolean InsertNewline)
{
	uint32 index = 0;
	char tempstr[16] = {0};

	(void)Local_itoa(num, tempstr, 10);

	while(tempstr[index] != (uint32)NULL)
	{
		(void)SEND_CHAR_TO_DEVICE(tempstr[index++]);
	}

	if(InsertNewline == ADD_NEWLINE)
	{
		(void)SEND_CHAR_TO_DEVICE('\n');
	}

	return ;
}


/* A utility function to reverse a string  */
static void reverse(char str[], uint32 length)
{
    uint32 start = 0;
    uint32 end = length -1;
    uint32 temp = 0;
    while (start < end)
    {
    	temp = *(str+start);
    	*(str+start) = *(str+end);
    	*(str+end) = temp;
        start++;
        end--;
    }
}

static char* Local_itoa(uint32 num, char* str, uint32 base)
{
	uint32 i = 0;
    _Bool isNegative = FALSE;

     /*Handle 0 explicitely, otherwise empty string is printed for 0*/
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard Local_itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = TRUE;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

#endif /*_PRINT_MODULE_*/
