/*
 * LCD.c
 *
 *  Created on: Feb 27, 2022
 *      Author: mohamed
 */
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "types_macros.h"
#include "LCD.h"

static _PORT LCD_PORT;
static _PORT CONTROL_PORT;
static uint8 RS_PIN;
static uint8 RW_PIN;
static uint8 EN_PIN;

void LCD_Init(const Configuration *confg){
	// Save the configuration data in the static variables
	LCD_PORT = confg->LCD_Port;
	CONTROL_PORT = confg->ControlPort;
	RS_PIN = confg->RS_Pin;
	RW_PIN = confg->RW_Pin;
	EN_PIN = confg->EN_Pin;
	// Delay for more than 30 ms
	_delay_ms(31);
	// Send Function Set Command
	LCD_SendCommand(FUNCTION_SET | confg->DL | confg->N | confg->F);
	// Delay for more than 39 us
	_delay_us(40);
	// Send Display_ON & Cursor_OFF Command
	LCD_SendCommand(DISPLAY_ON_CURSOR_OFF);
	// Delay for more than 39 us
	_delay_us(40);
	// Send Entry Mode Set Command
	LCD_SendCommand(ENTERY_MODE);
	// Delay for more than 39 us
	_delay_us(40);
	// Send Clear Display Command
	LCD_SendCommand(DISPLAY_CLEAR);
	// Delay for more than 1.53 ms
	_delay_ms(2);
}

void LCD_SendCommand(const uint8 Command){
	// SET RS -> 0 & RW -> 0
	switch(CONTROL_PORT){
		case PortA:
			CLEAR_BIT(PORTA, RS_PIN);
			CLEAR_BIT(PORTA, RW_PIN);
			break;
		case PortB:
			CLEAR_BIT(PORTB, RS_PIN);
			CLEAR_BIT(PORTB, RW_PIN);
			break;
		case PortC:
			CLEAR_BIT(PORTC, RS_PIN);
			CLEAR_BIT(PORTC, RW_PIN);
			break;
		case PortD:
			CLEAR_BIT(PORTD, RS_PIN);
			CLEAR_BIT(PORTD, RW_PIN);
			break;
	}
	// Wait for 1 us
	_delay_us(1);
	// Send Command to LCD Port
	switch(LCD_PORT){
		case PortA:
			PORTA = Command;
			break;
		case PortB:
			PORTB = Command;
			break;
		case PortC:
			PORTC = Command;
			break;
		case PortD:
			PORTD = Command;
			break;
	}
	// Wait for 1 us
	_delay_us(1);
	// Send Enable Signal to LCD EN Pin
	switch(CONTROL_PORT){
	    case PortA:
	    	SET_BIT(PORTA, EN_PIN);
	    	_delay_us(1);
	    	CLEAR_BIT(PORTA, EN_PIN);
	    	break;
	    case PortB:
	    	SET_BIT(PORTB, EN_PIN);
	    	_delay_us(1);
	    	CLEAR_BIT(PORTB, EN_PIN);
	    	break;
	    case PortC:
	    	SET_BIT(PORTC, EN_PIN);
	    	_delay_us(1);
	    	CLEAR_BIT(PORTC, EN_PIN);
	    	break;
	    case PortD:
	    	SET_BIT(PORTD, EN_PIN);
	    	_delay_us(1);
	    	CLEAR_BIT(PORTD, EN_PIN);
	    	break;
	}
	// Wait for 1 us
	_delay_us(1);
}

void LCD_PrintCharacter(const uint8 Character){
	// SET RS -> 1 & RW -> 0
	switch(CONTROL_PORT){
		case PortA:
			SET_BIT(PORTA, RS_PIN);
			CLEAR_BIT(PORTA, RW_PIN);
			break;
		case PortB:
			SET_BIT(PORTB, RS_PIN);
			CLEAR_BIT(PORTB, RW_PIN);
			break;
		case PortC:
			SET_BIT(PORTC, RS_PIN);
			CLEAR_BIT(PORTC, RW_PIN);
			break;
		case PortD:
			SET_BIT(PORTD, RS_PIN);
			CLEAR_BIT(PORTD, RW_PIN);
			break;
	}
	// Wait for 1 us
	_delay_us(1);
	// Send the character to LCD Port
	switch(LCD_PORT){
		case PortA:
			PORTA = Character;
			break;
		case PortB:
			PORTB = Character;
			break;
		case PortC:
			PORTC = Character;
			break;
		case PortD:
			PORTD = Character;
			break;
	}
	// Wait for 1 us
	_delay_us(1);
	// Send Enable Signal to LCD EN Pin
	switch(CONTROL_PORT){
	    case PortA:
	    	SET_BIT(PORTA, EN_PIN);
	    	_delay_us(1);
	    	CLEAR_BIT(PORTA, EN_PIN);
	    	break;
	    case PortB:
	    	SET_BIT(PORTB, EN_PIN);
	    	_delay_us(1);
	    	CLEAR_BIT(PORTB, EN_PIN);
	    	break;
	    case PortC:
	    	SET_BIT(PORTC, EN_PIN);
	    	_delay_us(1);
	    	CLEAR_BIT(PORTC, EN_PIN);
	    	break;
	    case PortD:
	    	SET_BIT(PORTD, EN_PIN);
	    	_delay_us(1);
	    	CLEAR_BIT(PORTD, EN_PIN);
	    	break;
	}
	// Wait for 1 us
	_delay_us(1);
}

void LCD_PrintString(const uint8* String){
	uint8 i = 0;
	while(String[i] != '\0'){
		LCD_PrintCharacter(String[i]);
		_delay_ms(50);
		i++;
	}
}

void LCD_intgerToString(int data)
{
   char buff[16];
   itoa(data,buff,10);
   LCD_PrintString(buff);
}
