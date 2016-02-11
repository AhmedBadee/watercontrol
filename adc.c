/*
 * adc.c
 *
 * Created: 10/3/2015 9:43:47 AM
 *  Author: Ahmed
 */ 

#include <avr/io.h>
#include "adc.h"

void adc_init() {
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

void adc_startConversion() {
	ADCSRA |= (1 << ADSC);
	while ((ADCSRA & (1 << ADIF)) == 0);
}

short adc_read() {
	short data;
	while ((ADCSRA & (1 << ADIF)) == 0);
	data = ADCL;
	data |= (ADCH << 8);
	return data;
}
