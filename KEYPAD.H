/*
 * KEYBAD.H
 *
 *  Created on: Mar 3, 2022
 *      Author: Hesham Ashraf
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "types_macros.h"


/*for keypad simplification*/
#define NUM_OF_COL 3 //number of keypad columns
#define NUM_OF_ROW 4 //number of keypad rows
#define KEYPAD_DDRX DDRC //for DDRX register used
#define KEYPAD_PORTX PORTC //for PORTX register used
#define KEYPAD_PINX PINC //for PINX register used
#define FIRST_COL PC4
#define FIRST_ROW PC0

uint8 get_Value(void);


#endif /* KEYPAD_H_ */
