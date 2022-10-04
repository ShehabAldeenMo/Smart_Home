/*
 * LCD.h
 *
 *  Created on: Feb 27, 2022
 *      Author: mohamed
 */

#ifndef LCD_H_
#define LCD_H_

// Configuration enums

// List of commands
typedef enum{
	DISPLAY_CLEAR = 0x01,   // Clear the display on the LCD and return to the first position
	HOME_RETURN = 0x02,     // Return to the first position
	ENTERY_MODE = 0x06,     // Each character sent to the LCD will be shifted right then printed
	DISPLAY_ON_CURSOR_ON_BLINKING = 0x0F,
	DISPLAY_ON_CURSOR_ON = 0x0E,
	DISPLAY_ON_CURSOR_OFF = 0x0C,
	DISPLAY_OFF_CURSOR_OFF = 0x08,
	DISPLAY_SHIFT_RIGHT = 0x1C, // Shift the entire display on the LCD to the right direction
	DISPLAY_SHIT_LEFT = 0x18,   // Shift the entire display on the LCD to the left direction
	CURSOR_SHIFT_RIGHT = 0x14,  // Shift the cursor (position of the next character) to the right direction
	CURSOR_SHIFT_LEFT = 0x10,   // Shift the cursor to the left direction
	NEXT_LINE = 0xC0, 			// move to the next line
	FUNCTION_SET = 0x20
}COMMAND_LIST;

// Enumeration for selecting the data transmission mode (4-bits or 8-bits)
typedef enum{
	_4bits = 0x00,
	_8bits = 0x10
}DATA_LENGTH;

// Enumeration for selecting the number of lines of the LCD
typedef enum{
	_1Line = 0x00,
	_2Line = 0x08
}NUM_LINES;

// Enumeration for selecting the character's font
typedef enum{
	_5_8  = 0x00,
	_5_10 = 0x04
}MATRIX_FONT;

// Enumeration for selecting the port
typedef enum{
	PortA,
	PortB,
	PortC,
	PortD
}_PORT;

// Configuration Structure
typedef struct{
	uint8 RS_Pin;      // Number of RS Pin in the Specified Control Port (can take value from 0 to 7)
	uint8 RW_Pin;      // Number of RW Pin in the Specified Control Port (can take value from 0 to 7)
	uint8 EN_Pin;      // Number of EN Pin in the Specified Control Port (can take value from 0 to 7)
	_PORT ControlPort;
	_PORT LCD_Port;
	DATA_LENGTH DL;
	NUM_LINES N;
	MATRIX_FONT F;
}Configuration;

// Functions prototypes
void LCD_Init(const Configuration *);
void LCD_SendCommand(const uint8);
void LCD_PrintCharacter(const uint8);
void LCD_PrintString(const uint8 *);
void LCD_intgerToString(int data);

#endif /* LCD_H_ */
