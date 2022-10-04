/*
 * ADC.h
 *
 *  Created on: Mar 10, 2022
 *  Author: Shehab aldeen 
 */

#ifndef ADC_H_
#define ADC_H_

#define ADC_V_REF 5 //volts of the v_ref
#define MAX_VALUE_ADC_REP 1023 //the max binary value foe the ADC
/*function used to initialize the ADC driver*/
void ADC_init(void);

/*Function takes the channel number and return the ADC register value "binary
 * representaion for the out world data"*/
uint16 ADC_readChannel(uint8);




#endif /* ADC_H_ */
