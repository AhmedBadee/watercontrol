/*
 * app.c
 *
 *  Created on: Feb 5, 2016
 *      Author: ahmed
 */
#include <avr/io.h>
#include <stdlib.h>
#include "app.h"
#include "lcd.h"

	int i = 0;

//Ports Initialization
void ports_init() {
	DDRB = 0x00;
	DDRD = 0x70;

	PINB = 0x00;
	PIND = ~(1 << PD0) & ~(1 << PD1) & ~(1 << PD2) & ~(1 << PD3) & ~(1 << PD4);

	PORTD &= ~(1 << PD7);
}

void valve(int currentLevel, int targetLevel) {
	if (currentLevel < targetLevel)
		PORTD |= (1 << PD7);
	else
		PORTD &= ~(1 << PD7);
}

//Current Level mapping
int transistors_read(int transistorsRead, int currentLevel) {
	switch(transistorsRead) {
		case 0:
			currentLevel = 0;
			break;
		case 1:
			currentLevel = 1;
			break;
		case 3:
			currentLevel = 2;
			break;
		case 7:
			currentLevel = 3;
			break;
		case 15:
			currentLevel = 4;
			break;
		case 31:
			currentLevel = 5;
			break;
		case 63:
			currentLevel = 6;
			break;
		case 127:
			currentLevel = 7;
			break;
		case 255:
			currentLevel = 8;
			break;
		case 511:
			currentLevel = 9;
			break;
		case 1023:
			currentLevel = 10;
			break;
		case 2047:
			currentLevel = 11;
			break;
		case 4093:
			currentLevel = 12;
			break;
		}
	return currentLevel;
}

//Target Level mapping
int target_level(int data, int targetLevel) {
	for (i = 0; i < 14; i++)
	{
		if ((data >= ((1024/13)*(i-1))) && (data < (1023/13) * i)) {
			targetLevel= i - 1;
			break;
		}
	}
	return targetLevel;
}

void display_height(int currentLevel, char current_height[]) {
	for (i = 0; i <= 12; i++) {
		if (currentLevel == i) {
			itoa(currentLevel, current_height, 10);
			lcd_command(0xC0);
			lcd_string(" CL= ");
			lcd_string(current_height);
			lcd_string(" cm");
			break;
		}
	}
}
