/*
 * ADC.c
 *
 *  Created on: Mar 10, 2022
 *  Author: Shehab aldeen 
 */
#include <avr/io.h>
#include "types_macros.h"
#include "ADC.h"

void ADC_init(){
	/*Data required in the ADMUX register
	  1- select the v_ref source
	  2- select the data type adjustment "usually use 0"
	  3- clear the channel multiplexer
	*/
	/*select the AREF REFS1 = 0 and REFS0 = 0 */
	ADMUX = 0;

	/*Data required in the ADCSRA register
	 1- enable the ADC
	 2- select the pre-scaler
	 3- we can enable the interrupt if we want
	 */
	// Enable the ADC and pre-scaller 8
	ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
}

uint16 ADC_readChannel(uint8 channel_num){
	/*clear the multiplexing bits 3shan law kan fe channel m5tarha abl kda*/
	ADMUX = 0XE0; //clear the first 5 bits
	ADMUX = ADMUX | (channel_num & (0X1F));

	/*set the start conversion bit*/
	SET_BIT(ADCSRA , ADSC);
	/*hanging the code until the conversion ends*/
	while(BIT_IS_CLEAR(ADCSRA , ADIF));
	 /*Clear the flag*/
	SET_BIT(ADCSRA , ADIF);

	return ADC;
}

