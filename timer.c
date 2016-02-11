/** timer.c
 *
 *  Created on: Feb 4, 2016
 *      Author: ahmed
 */

#include <avr/io.h>
#include "timer.h"

void timer_init() {
	TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);
	TIMSK = (1 << OCIE1A);
}

void timer_value(int period) {
	OCR1AL = period;
}
