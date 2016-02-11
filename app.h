/*
 * app.h
 *
 *  Created on: Feb 5, 2016
 *      Author: ahmed
 */

#ifndef APP_H_
#define APP_H_

void ports_init();
void valve(int currentLevel, int targetLevel);
int transistors_read(int transistorsRead, int currentLevel);
int target_level(int data, int targetLevel);
void display_height(int currentLevel, char current_height[]);

#endif /* APP_H_ */
