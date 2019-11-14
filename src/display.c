#include "display.h"

#define CLK (1<<0)
#define LAT (1<<1)
#define OE (1<<2)
#define R1 (1<<4)
#define G1 (1<<5)
#define B1 (1<<6)
#define R2 (1<<7)
#define G2 (1<<8)
#define B2 (1<<9)

int Count = 0;
int lineSelect = 0;

void setup_timer6() { // TIMER6 controls data writing
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    TIM6->PSC = 48-1;
    TIM6->ARR = 10-1;
    TIM6->DIER |= TIM_DIER_UIE;
    TIM6->CR1 = TIM_CR1_CEN;
    NVIC->ISER[0] = (1<<TIM6_DAC_IRQn);
}

void TIM6_DAC_IRQHandler() {
    TIM6->SR &= ~TIM_SR_UIF;

    GPIOA->ODR |= CLK;  // turn on clock
    setRGB();         // setup RGB data
    GPIOA->ODR &= ~CLK; // turn off clock

    Count++;
    if(Count == 64) {
        GPIOA->ODR |= CLK;  // turn on clock
        GPIOA->ODR |= LAT;  // pull the LAT high to enable it
        GPIOA->ODR |= OE;  // pull the OE high to disable it
        GPIOA->ODR &= ~CLK; // turn off clock

        // switch rows by driving the appropriate row select lines
        GPIOA->ODR |= CLK; // turn on clock
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
        GPIOA->ODR &= ~CLK; // turn off clock

        GPIOA->ODR |= CLK;  // turn on clock
        GPIOA->ODR &= ~LAT; // pull the LAT low to disable it
        GPIOA->ODR &= ~OE; // pull the OE low to enable it
        GPIOA->ODR &= ~CLK; // turn off clock

        Count = 0;
    }
}

void setRGB() {
    // construct the frame (will stay)
    GPIOA->ODR &= ~(R1 | G1 | B1 | R2 | G2 | B2); // reset all RGBs

    switch(lineSelect) {
    case  0: GPIOA->ODR |= R1 | G1; break;
    case  1: ; break;
    case  2: ; break;
    case  3: ; break;
    case  4: ; break;
    case  5: ; break;
    case  6: ; break;
    case  7: ; break;
    case  8: ; break;
    case  9: ; break;
    case 10: ; break;
    case 11: ; break;
    case 12: ; break;
    case 13: ; break;
    case 14: ; break;
    case 15: GPIOA->ODR |= R2 | G2; break;
    default: GPIOA->ODR &= ~(R1 | G1 | B1 | R2 | G2 | B2); // reset all RGBs
    }
}
