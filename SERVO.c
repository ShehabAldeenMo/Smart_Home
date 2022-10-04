/*
 * SERVO.c
 *
 *  Created on: Mar 16, 2022
 *      Author: hp
 */
#include "SERVO.h"

void servo_init()
{
	SET_BIT(DDRD,5);
}


void servo_rotate(float ang)
{
	float ang2 = 90 + ang ;
		TCCR1A = (1<<WGM11)|(1<<COM1A1) ; // set PWM mode to timer1
		TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS11); // set mode 14 and prescaler 8.
		ICR1 = 2499 ;// something i do not know.
		SET_BIT(DDRD,5);
		OCR1A = (((1+(ang2/180))*1000)/8) ;
}
