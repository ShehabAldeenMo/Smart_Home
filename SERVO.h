/*
 * SERVO.h
 *
 *  Created on: Mar 16, 2022
 *      Author: hp
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <avr/io.h>
#include "types_macros.h"
#include "timer.h"


void servo_init();

void servo_rotate(float ang);

#endif /* SERVO_H_ */
