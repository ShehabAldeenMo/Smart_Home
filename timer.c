/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.c
 *
 * Description: Source file for the AVR TIMERS driver
 *
 * Author: Mohamed Mahmoud
 *
 *******************************************************************************/
/************************************ Headers **********************************/
#include "avr/io.h"	/* to use Timers Registers */
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"
#include "LCD.h"
#include "SERVO.h"
#include "lm35_sensor.h"
/*********************** Interrupt Service Routines ****************************/
uint8 th[20] = "Theft Attempted";
uint8 trick = 0;// counter to count the number of overflowes
uint8 e = 0;
ISR(TIMER0_OVF_vect)
{//timer0 work win the password is wrong for three times
	trick++;
	TOGGLE_BIT(PORTD,0);
	if(trick == 97)// when the prescaler is 1024 so every four overflow take one second
	{
		CLEAR_BIT(PORTD,0);// after 30 seconds of toggling
		trick=0;// the counter is zero
		Timer_DeInit(TIMER0);// deinit the timer
	}


}
ISR(TIMER0_COMP_vect)
{

}
ISR(TIMER1_OVF_vect)
{
	}
ISR(TIMER1_COMPA_vect)
{
}
ISR(TIMER2_OVF_vect)
{// timer2 works when the password is right to open the door
	trick++;// we are in over flow mode so we use a counter
		servo_init();//init the pin of the motor
		servo_rotate(90);// open the door by 90 degrees
		if(trick == 20)// the prescaler is 1024 so each 4 overflow make one second and we need five seconds
		{
			servo_rotate(0);// after 5 seconds the door is closed
			trick = 0; //clear the tick counter again to count a new second
			Timer_DeInit(TIMER2);// put the action that you want to happens after one second
		}

}
ISR(TIMER2_COMP_vect)
{

}

/***********************  Functions Definitions  ***************************/
/* Description:
 * The Function to initialize the Timer according to passed configuration struct
 * 1.select which timer to use
 * 2.set required timer mode
 * 3.set required prescalar
 * 4.initialize initial count register as required
 * 5.set compare value as required if compare mode is chosen
 */
void Timer_init(const Timer_ConfigType* config_ptr){
	switch(config_ptr->number)
	{
	/* Timer0 initialization */
	case TIMER0:
		/* Set Timer initial value */
		TCNT0 = (uint8)config_ptr->initialCounter;
		/* Non PWM mode FOC0=1 */
		SET_BIT(TCCR0,FOC0);
		/* set prescalar value */
		TCCR0 = (TCCR0 & 0xF8) | (config_ptr->prescalar & 0x07);
		if (config_ptr->mode == COMPARE){
			/* select compare mode WGM01=1 */
			SET_BIT(TCCR0,WGM01);
			/* Set Compare Value */
			OCR0 = (uint8)config_ptr->compareValue;
			/* Enable Timer0 compare interrupt */
			SET_BIT(TIMSK,OCIE0);
		}
		else if(config_ptr->mode == NORMAL){
			/* Enable Timer0 overflow interrupt */
			SET_BIT(TIMSK,TOIE0);
		}
		break;

		/* Timer1 initialization */
	case TIMER1:
		/* Set Timer initial value */
		TCNT1 = config_ptr->initialCounter;
		/* Non PWM mode FOC1A=1 , FOC1B=1 */
		SET_BIT(TCCR1A, FOC1A);
		SET_BIT(TCCR1A, FOC1B);
		/* set prescalar value */
		TCCR1B = (TCCR1B & 0xF8) | (config_ptr->prescalar & 0x07);
		if (config_ptr->mode == COMPARE){
			/* select compare mode */
			SET_BIT(TCCR1B,WGM12);
			/* Set Compare Value */
			OCR1A = config_ptr->compareValue;
			/* Enable Timer1 compareA interrupt */
			SET_BIT(TIMSK,OCIE1A);
		}
		else if(config_ptr->mode == NORMAL){
			/* Enable Timer1 overflow interrupt */
			SET_BIT(TIMSK,TOIE1);
		}
		break;

		/* Timer2 initialization */
	case TIMER2 :
		/* Set Timer initial value */
		TCNT2 = (uint8)config_ptr->initialCounter;
		/* Non PWM mode FOC2=1 */
		SET_BIT(TCCR2,FOC2);
		/* set prescalar value */
		TCCR2 = (TCCR2 & 0xF8) | (config_ptr->prescalar & 0x07);
		if (config_ptr->mode == COMPARE){
			/* select compare mode WGM21=1 */
			SET_BIT(TCCR2,WGM21);
			/* Set Compare Value */
			OCR2 = (uint8)config_ptr->compareValue;
			/* Enable Timer2 compare interrupt */
			SET_BIT(TIMSK,OCIE2);
		}
		else if(config_ptr->mode == NORMAL){
			/* Enable Timer2 overflow interrupt */
			SET_BIT(TIMSK,TOIE2);
		}
		break;
	}
}


/* Description:
 * The Function responsible for disable specific timer (0, 1 or 2) after using it
 */
void Timer_DeInit(Timer_Number number){
	switch(number)
	{
	/* Disable Timer0 by writing 0 in its registers and disable its interruts bits */
	case TIMER0:
		TCCR0 = 0;
		TCNT0 = 0;
		OCR0 = 0;
		CLEAR_BIT(TIMSK,TOIE0);
		CLEAR_BIT(TIMSK,OCIE0);
		break;
		/* Disable Timer1 by writing 0 in its registers and disable its interruts bits */
	case TIMER1:
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1 = 0;
		OCR1A = 0;
		OCR1B = 0;
		CLEAR_BIT(TIMSK,TOIE1);
		CLEAR_BIT(TIMSK,OCIE1A);
		CLEAR_BIT(TIMSK,OCIE1B);
		break;
		/* Disable Timer2 by writing 0 in its registers and disable its interruts bits */
	case TIMER2:
		TCCR2 = 0;
		TCNT2 = 0;
		OCR2 = 0;
		CLEAR_BIT(TIMSK,TOIE2);
		CLEAR_BIT(TIMSK,OCIE2);
		break;
	}
}
