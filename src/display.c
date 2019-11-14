#include "display.h"

void setup_timer6() { // TIMER6 controls data writing
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    TIM6->PSC = 48-1;
    TIM6->ARR = 10-1;
    TIM6->DIER |= TIM_DIER_UIE;
    TIM6->CR1 = TIM_CR1_CEN;
    NVIC->ISER[0] = (1<<TIM6_DAC_IRQn);
}

int Count = 0;
int lineSelect = 0;

void TIM6_DAC_IRQHandler() {
    TIM6->SR &= ~TIM_SR_UIF;

    GPIOA->ODR |= 1;  // turn on clock
    setRGB();         // setup RGB data
    GPIOA->ODR &= ~1; // turn off clock

    Count++;
    if(Count == 64) {
        GPIOA->ODR |= 1;  // turn on clock
        GPIOA->ODR |= 2;  // pull the LAT high to enable it
        GPIOA->ODR |= 4;  // pull the OE high to disable it
        GPIOA->ODR &= ~1; // turn off clock

        // switch rows by driving the appropriate row select lines
        GPIOA->ODR |= 1; // turn on clock
        if(lineSelect % 2) {
            GPIOA->ODR |= 1<<10;
        } else {
            GPIOA->ODR &= ~(1<<10);
        }
        if(lineSelect % 4 >= 2) {
            GPIOA->ODR |= 1<<11;
        } else {
            GPIOA->ODR &= ~(1<<11);
        }
        if(lineSelect % 8 >= 4) {
            GPIOA->ODR |= 1<<12;
        } else {
            GPIOA->ODR &= ~(1<<12);
        }
        if(lineSelect % 16 >= 8) {
            GPIOA->ODR |= 1<<13;
        } else {
            GPIOA->ODR &= ~(1<<13);
        }
        if(lineSelect >= 15) {
            lineSelect = 0;
        } else {
            lineSelect += 1;
        }
        GPIOA->ODR &= ~1; // turn off clock

        GPIOA->ODR |= 1;  // turn on clock
        GPIOA->ODR &= ~2; // pull the LAT low to disable it
        GPIOA->ODR &= ~4; // pull the OE low to enable it
        GPIOA->ODR &= ~1; // turn off clock

        Count = 0;
    }
}

void setRGB() {

}
