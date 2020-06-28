/*************************************************************************************************
 * Module name: PRINT.h
 *
 * Purpose:This module provides print functionality to output messages, with a very minimal memory
 * 			cost. This module can be mapped to use built-in ITM, or external LCD or UART.
 *
 * Created on: 24-Apr-2020
 *
 * Author: Vineet
 *************************************************************************************************/

#ifndef BSW_PRINT_H_
#define BSW_PRINT_H_


/*************************************************************************************************
 *	Includes
 *************************************************************************************************/

/*************************************************************************************************
 *	MACRO
 *************************************************************************************************/
#define NO_NEWLINE	FALSE
#define ADD_NEWLINE TRUE

/*************************************************************************************************
 *	Private variables
 *************************************************************************************************/


/*************************************************************************************************
 *	Global variables
 *************************************************************************************************/


/*************************************************************************************************
 *	Function prototypes
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
uint8 PRINT_String(char *str, boolean InsertNewline);

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
void PRINT_Number(uint32 num, boolean InsertNewline);

/*************************************************************************************************
 *	Function Definitions
 *************************************************************************************************/


/*************************************************************************************************
 *  @name - 
 *
 *  @summary - 
 *
 *  @param - 
 *
 *  @retval- 
 *************************************************************************************************/

#endif /* BSW_PRINT_H_ */
