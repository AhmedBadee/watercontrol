#include <avr/io.h>
#include <util/delay.h>
#include "defines.h"
#include "lcd.h"

void lcd_init() {
	DDRC = 0xFF;
	DDRA = 0xE0;

	PORTA &= ~(1 << EN);                       // EN = 0
	_delay_ms(2000);

	lcd_command(0x38);                         // 8 Bit mode   D0-D7
	_delay_us(100);
	lcd_command(0x0E);                         // Display on, Cursor on
	_delay_us(100);
	lcd_command(0x01);                         // Clear
	_delay_ms(2);
}

void lcd_data(char data) {
	PORTC = data;

	PORTA |= (1 << RS);                        // RS = 1  Data mode
	PORTA &= ~(1 << RW);                       // RW = 0  Write mode
	PORTA |= (1 << EN);
	_delay_us(1);
	PORTA &= ~(1 << EN);
	_delay_us(100);
}

void lcd_command(char cmd) {
	PORTC = cmd;

	PORTA &= ~(1 << RS);                       // RS = 0 Command mode
	PORTA &= ~(1 << RW);					   // RW = 0 Write mode
	PORTA |= (1 << EN);
	_delay_us(1);
	PORTA &= ~(1 << EN);
	_delay_us(100);
}

void lcd_string(char *data) {
	while(*data) {
		lcd_data(*data++);
		_delay_ms(80);                        // 50 Milliseconds (minimum)
	}
}
