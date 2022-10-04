/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.h
 *
 * Description: Header file for the AVR TIMERS driver
 *
 * Author: Mohamed Mahmoud
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "types_macros.h"

/************************ Types Declaration ******************************/
typedef enum
{
	TIMER0,TIMER1,TIMER2
}Timer_Number;
typedef enum
{
	NORMAL,COMPARE
}Timer_Mode;
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,F_CPU_1024_timer2 = 7
}Timer_Prescalar;

/* Timer configuration structure */
typedef struct
{
	Timer_Number number;
	Timer_Mode mode;
	Timer_Prescalar prescalar;
	uint16 initialCounter;	/* 16 bits because of Timer1 and will be casted in Timer0 & Timer2 */
	uint16 compareValue;	/* 16 bits because of Timer1 and will be casted in Timer0 & Timer2 */
}Timer_ConfigType;

/***********************  Functions Prototypes  ***************************/
/* Description:
 * The Function to initialize the Timer according to passed configuration struct
 * 1.select which timer to use
 * 2.set required timer mode
 * 3.set required prescalar
 * 4.initialize initial count register as required
 * 5.set compare value as required if compare mode is chosen
 */
void Timer_init(const Timer_ConfigType* config_ptr);

/* Description:
 * The Function responsible for disable specific timer (0, 1 or 2) after using it
 */
void Timer_DeInit(Timer_Number number);

#endif /* TIMER_H_ */
