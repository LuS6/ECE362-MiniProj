#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

int get_key_press();
int get_key_release();
int get_key_pressed();
char get_char_key();
void setup_timer3();
void TIM3_IRQHandler();
void key_function();

#endif /* KEYPAD_H_ */
