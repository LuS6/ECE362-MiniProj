#include "keypad.h"

// get key press
int get_key_press() {
    while(1) {
        for(int i = 0; i < 16; i++) {
            if(keypad[i] == 1) {
                return i;
            }
        }
    }
}

int get_key_release() {
    while(1) {
        for(int i = 0; i < 16; i++) {
            if(keypad[i] == -2) {
                return i;
            }
        }
    }
}

// get pressed key information
int get_key_pressed() {
    int key = get_key_press();
    while(key != get_key_release());
    return key;
}

char get_char_key() {
    int index = get_key_pressed();
    return char_lookup[index];
}

void setup_timer3() { // TIMER3 controls keypad functions
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->PSC = 480-1;
    TIM3->ARR = 100-1;
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1 = TIM_CR1_CEN;
    NVIC->ISER[0] = (1<<TIM3_IRQn);
}

void TIM3_IRQHandler() {
    TIM3->SR &= ~TIM_SR_UIF;
    int row = (GPIOB->IDR >> 4) & 0xf;
    int index = (col << 2);
    keypad[index]   <<= 1;
    keypad[index+1] <<= 1;
    keypad[index+2] <<= 1;
    keypad[index+3] <<= 1;
    keypad[index]   |= row & 0x1;
    keypad[index+1] |= (row >> 1) & 0x1;
    keypad[index+2] |= (row >> 2) & 0x1;
    keypad[index+3] |= (row >> 3) & 0x1;
    col++;
    col = col > 3 ? 0: col;
    GPIOB->ODR = (1 << col);
}

// key functions
void key_function() {
    while(1) {
        char key = get_char_key();
        switch (key){
            case '1': RCC->AHBRSTR |= RCC_AHBRSTR_GPIOARST; //reset
                break;
            case '2': RCC->AHBENR &= ~RCC_AHBENR_GPIOAEN; //rotate
                break;
            case '3': RCC->AHBENR |= RCC_AHBENR_GPIOAEN
                    ; // nothing
                break;
            case '4': ; // move left
                break;
            case '5': ; // immediate drop
                break;
            case '6': ; // move right
                break;
            default: ; // no action
        }
    }
}
