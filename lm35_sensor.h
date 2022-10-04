#ifndef LM35_SENSOR_H_
#define LM35_SENSOR_H_

#include "types_macros.h"
#include "avr/io.h"	/* to use Timers Registers */
#include <util/delay.h>
#include "timer.h"
#include "LCD.h"
#include "SERVO.h"
#include "ADC.h"



#define SENSOR_CHANNEL_ID         2// the pin of the sensor
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150

void ADC_init();

uint8 LM35_readtemp(void);

void check();

#endif
