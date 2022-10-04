#include "lm35_sensor.h"
#include "ADC.h"

uint8 HT[20] = "HIGH TEMPRATURE";

/*********************************************************************************************************************************************************************/

uint8 LM35_readtemp(void)
{

	uint8 temp_value = 0;     // a temporary variable to save the temperature value
    uint16 adc_value = 0;     // a temporary variable to save the adc readings
    float tempo = 0;

	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);// take the value read by the ADC

	temp_value = (uint8)(((uint32)adc_value*SENSOR_MAX_TEMPERATURE*ADC_V_REF)/(MAX_VALUE_ADC_REP*SENSOR_MAX_VOLT_VALUE));

	tempo = adc_value / 256 ;// i noticed that one degree on the sensor make the adc read the value 256 so our needed temp is the adc_value over 256.

	// interpolation equation used to obtain the temperature via the ADC readings
	return tempo;
}

/*******************************************************************************************************************************************************************/

void check()// this function is to check the temperature at any time by using it many times at the main.
{
	if(LM35_readtemp() >= 30)// if the temp exceeds 30
	{
		SET_BIT(PORTA,7);//light up
		SET_BIT(PORTA,6);
		SET_BIT(PORTA,5);

		servo_init();
		servo_rotate(90);//open the door

		LCD_SendCommand(DISPLAY_CLEAR);
		_delay_ms(20);
		LCD_PrintString(HT);//display high temprature
		_delay_ms(20);
		LCD_SendCommand(NEXT_LINE);
		_delay_ms(20);
		LCD_intgerToString(LM35_readtemp());// display the temp
		_delay_ms(20);
		while(LM35_readtemp()>=30)
		{
			// out only when the temp is lower than 30
		}
		servo_rotate(0);// close the door
		CLEAR_BIT(PORTA,7);// light off
		CLEAR_BIT(PORTA,6);
		CLEAR_BIT(PORTA,5);
	}

}

