#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

int col = 0;
int8_t keypad[16] = {0};
int8_t lookup[16] = {1,4,7,0xe,2,5,8,0,3,6,9,0xf,0xa,0xb,0xc,0xd};
char char_lookup[16] = {'1','4','7','*','2','5','8','0','3','6','9','#','A','B','C','D'};

int get_key_press();
int get_key_release();
int get_key_pressed();
char get_char_key();
void setup_timer3();
void TIM3_IRQHandler();
void key_function();

#endif /* KEYPAD_H_ */
