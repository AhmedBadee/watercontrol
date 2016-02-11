#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include "lcd.h"
#include "adc.h"
#include "defines.h"
#include "timer.h"
#include "app.h"

	char max_height[4];
	char current_height[4];
	int currentLevel = 0;
	int transistorsRead = 0;
	long data = 0;
	int targetLevel = 0;
	int PINDRead = 0;

int main() {

	//Initialization
	ports_init();
	timer_init();
	lcd_init();
	adc_init();
	sei();

	timer_value(7811);

	while(1) {}
}

ISR(TIMER1_COMPA_vect) {

	adc_startConversion();
	data = adc_read();

	lcd_command(0x01);
	_delay_ms(50);

	// Potentiometer mapping
	targetLevel = target_level(data, targetLevel);

	itoa(targetLevel, max_height, 10);

	//
	PINDRead = PIND & 0x0F;
	transistorsRead = PINB | PINDRead;

	//Current Level mapping
	currentLevel = transistors_read(transistorsRead, currentLevel);

	//Controlling the valve
	valve(currentLevel, targetLevel);

	//Displaying target level
	lcd_command(0x80);
	lcd_string(" TL= ");
	lcd_string(max_height);
	lcd_string(" cm");

	//Displaying height
	display_height(currentLevel, max_height);
}
