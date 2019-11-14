#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

int Count = 0;
int lineSelect = 0;

void setup_timer6();
void TIM6_DAC_IRQHandler();
void setRGB();

#endif /* DISPLAY_H_ */
