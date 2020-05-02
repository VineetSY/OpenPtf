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


/*************************************************************************************************
 *	Private variables
 *************************************************************************************************/


/*************************************************************************************************
 *	Global variables
 *************************************************************************************************/


/*************************************************************************************************
 *	Function prototypes
 *************************************************************************************************/
uint8 PRINT_String(char *str, uint32 num);

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
