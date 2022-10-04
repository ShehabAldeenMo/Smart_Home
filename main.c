/*
 * main.c
 *
 *  Created on: Mar 12, 2022
 *  Author: Shehab aldeen
 */

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "types_macros.h"
#include "KEYPAD.H"
#include "LCD.h"
#include "SERVO.h"
#include "lm35_sensor.h"


int main()
{
	SET_BIT(SREG,7);// set the global interrupt flag because of the timers

	CLEAR_BIT(DDRA,2);// make the pin of the sensor as input
	DDRB = 0xff;//activate the lcd data port
	PORTB = 0;

	DDRD = 0x0E;// activate control port lcd
	PORTD = 0;

	SET_BIT(DDRD,0);// active the led pin
	CLEAR_BIT(PORTD,0);

	Configuration lcd = {1 ,2 ,3 , PortD , PortB , _8bits ,_2Line,_5_10};// state the lcd structure
	LCD_Init(&lcd);

	DDRC = 0xf0;// active the port of the keypad

	servo_init();// activate the motor pin

	ADC_init();// activate the ADC

	// some strings to the lcd .
	uint8 in[16] = "ENTER PASSWORD.";
	uint8 con[11] = "CONFIRMED.";
	uint8 wor[10] = "WRONG.";
	uint8 stl[16] = " ATTEMPTS LEFT.";
	uint8 fir[11] = "ENTER NEW ";
	uint8 sec[15] = "PLEASE CONFIRM";
	uint8 it[3] = "IT";
	uint8 is[4] = "IS ";
	uint8 thir[10] = "UNMATCHED";
	uint8 th[16] = "THEFT ATTEMPTED";
	uint8 tem[16] = "THE TEMPERATURE";
	uint8 o[5] = "'C";
	uint8 wel[9] = "PASSWORD";

	// num1 array to get the password into it
	uint8 num1[6] = { 5,5,5,5,5 };
	// num2 array to compare it with num1 to confirm the password
	uint8 num2[6] ;

	Timer_ConfigType timer2 = {TIMER2 , NORMAL , F_CPU_1024_timer2 , 0 , 0 };// timer2 to open the door when the password is correct
	Timer_ConfigType timer0 = {TIMER0 , NORMAL , F_CPU_1024 , 0 , 0 };// timer1 to set the alarms for the thieves

	SET_BIT(DDRA,7);// make the leds of the high temperature as output
	SET_BIT(DDRA,6);
	SET_BIT(DDRA,5);

	uint8 i = 0;
	uint8 flag1 = 0;
	uint8 flag2 = 0;
	uint8 trick = 0;
	uint8 temp = 0;
	uint8 r = 0;

	while(1)
	{
		check();// check high temperature
		while(1)// while loop till the user enter the new password and confirm it.
		{
			check();// check high temperature
			LCD_SendCommand(DISPLAY_CLEAR);// first clear the lcd
			_delay_ms(20);
			LCD_PrintString(fir); // display string enter new.
			_delay_ms(20);
			LCD_SendCommand(NEXT_LINE); // new function i made it to go to the next line of the lcd.
			_delay_ms(20);
			LCD_PrintString(wel); // print the string password
			_delay_ms(20);
			for(i=0 ; i<5 ; i++) // for loop of five to insert five digits.
			{
				check();// check high temperature
				num1[i] = get_Value();
				if(i==0)
					LCD_SendCommand(DISPLAY_CLEAR);// first clear the lcd.
				else
					LCD_SendCommand(CURSOR_SHIFT_RIGHT);// after that every time after inserting a new digit shift right.
				_delay_ms(20);
				LCD_PrintCharacter(num1[i] + 48);// display the number.
				_delay_ms(500);
			}
			// after that show the next string
			LCD_SendCommand(DISPLAY_CLEAR);
			_delay_ms(20);
			LCD_PrintString(sec);
			_delay_ms(20);
			LCD_SendCommand(NEXT_LINE);
			_delay_ms(20);
			LCD_PrintString(it);
			_delay_ms(20);

			for(i=0 ; i<5 ; i++)// in this for loop we repeat the previous loop but for num2 to confirm
			{
				check();// check high temperature
				num2[i] = get_Value();// get the value of the keypad
				if(i==0)
					LCD_SendCommand(DISPLAY_CLEAR);// clear the lcd at first
				else
					LCD_SendCommand(CURSOR_SHIFT_RIGHT);// shift after each insertion
				_delay_ms(20);
				LCD_PrintCharacter(num2[i] + 48);// display the number on the lcd
				_delay_ms(500);
			}

			for(i=0 ; i<5 ; i++)// here we compare num1 and num2
			{
				if(num1[i] != num2[i])
				{
					check();
					LCD_SendCommand(DISPLAY_CLEAR);
					_delay_ms(20);
					LCD_PrintString(thir);// the string unmatched.
					_delay_ms(1000);
					flag1 = 0;
					break;
				}
				else
					flag1 = 1;
			}

			if(flag1 == 1)// if num1 == num2 break from while
				break;
		}
		/****************************************************************************************************************************************************************************************/
		LCD_SendCommand(DISPLAY_CLEAR);
		_delay_ms(20);
		LCD_PrintString(con);// string confirmed
		_delay_ms(2000);
		/******************************************   AFTER THE CONFIRMATION OF THE PW NOW WE ASK FOR THE RIGHT PW    ***************************************************************************/
		while(1)
		{
			check();// check high temperature
			LCD_SendCommand(DISPLAY_CLEAR);
			_delay_ms(20);
			LCD_PrintString(in);// the string enter password
			_delay_ms(20);
			// the r for loop to dedicate the wrong pw times
			for(r=0 ; r<3 ;r++)
			{
				check();
				//the i for loop to receive the input password from the user
				for(i=0 ; i<5 ; i++)
				{
					check();
					num2[i] = get_Value();
					if(i==0)
						LCD_SendCommand(DISPLAY_CLEAR);
					else
						LCD_SendCommand(CURSOR_SHIFT_RIGHT);
					_delay_ms(20);
					LCD_PrintCharacter(num2[i] + 48);
					_delay_ms(500);
				}
				//the next for loop to compare the input with the right password
				for(i=0 ; i<5 ; i++)
				{
					if(num1[i] != num2[i])
					{
						LCD_SendCommand(DISPLAY_CLEAR);
						_delay_ms(20);
						LCD_PrintString(wor);
						_delay_ms(1000);
						LCD_SendCommand(DISPLAY_CLEAR);
						_delay_ms(20);
						LCD_PrintCharacter((2-r) + 48 );
						LCD_SendCommand(CURSOR_SHIFT_RIGHT);
						LCD_PrintString(stl);
						flag2 = 0;// if there is any miss match clear the flag and break the loop
						break;
					}
					else if(i==4)
					{
						flag2 = 1; // if the counter reach 4 set the flag and break the loop.
						break;
					}
				}
				/***************************************************************************************************************************/
				if(flag2 == 1)// as soon as the flag is one break the bigger loop
				{break;}
				else if(flag2==0 && r==2)// if the flag is clear and the counter of the bigger loop is 2 break the loop
				{break;}
			}
			if(flag2 == 0)// if wrong password
			{
				check();
				Timer_init(&timer0);
				LCD_SendCommand(DISPLAY_CLEAR);
				_delay_ms(20);
				LCD_PrintString(th);// the string theft attempted
				while(trick<23)//hang the system for 30 seconds , 23 is an approximate number to reach 30 seconds in real time.
				{// this delay is used to keep the string "theft attempted" displayed on the lcd
					_delay_ms(1000);
					trick++;
				}
				trick = 0;
			}
			else if(flag2 == 1)// if true password
			{
				temp = LM35_readtemp();// read the temperature
				Timer_init(&timer2);// init the timer to open the door
				LCD_SendCommand(DISPLAY_CLEAR);
				_delay_ms(20);
				LCD_PrintString(tem);// the string the temperature
				_delay_ms(20);
				LCD_SendCommand(NEXT_LINE);//go to the next line
				_delay_ms(20);
				LCD_PrintString(is);// print is
				_delay_ms(20);
				LCD_intgerToString(temp);// print the degree
				_delay_ms(20);
				LCD_PrintString(o);// print 'C
				while(trick<5)//hang the system for 5 seconds till the door is closed.
				{// this delay is used to keep the string of the temperature displayed on the lcd
					_delay_ms(1000);
					trick++;
				}
				trick = 0;
			}
		}



	}
}
