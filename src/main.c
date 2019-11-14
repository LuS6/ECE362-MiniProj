#include "display.h"
#include "keypad.h"
			
void setup_gpio() {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    // PA0 for CLK, PA1 for LAT, PA2 for OE
    GPIOA->MODER |= GPIO_MODER_MODER0_0
                  | GPIO_MODER_MODER1_0
                  | GPIO_MODER_MODER2_0
                  | GPIO_MODER_MODER4_0 // R1
                  | GPIO_MODER_MODER5_0 // G1
                  | GPIO_MODER_MODER6_0 // B1
                  | GPIO_MODER_MODER7_0 // R2
                  | GPIO_MODER_MODER8_0 // G2
                  | GPIO_MODER_MODER9_0 // B2
                  | GPIO_MODER_MODER10_0 // A
                  | GPIO_MODER_MODER11_0 // B
                  | GPIO_MODER_MODER12_0 // C
                  | GPIO_MODER_MODER13_0; // D
    GPIOA->MODER &= ~(GPIO_MODER_MODER0_1
                    | GPIO_MODER_MODER1_1
                    | GPIO_MODER_MODER2_1
                    | GPIO_MODER_MODER4_1 // R1
                    | GPIO_MODER_MODER5_1 // G1
                    | GPIO_MODER_MODER6_1 // B1
                    | GPIO_MODER_MODER7_1 // R2
                    | GPIO_MODER_MODER8_1 // G2
                    | GPIO_MODER_MODER9_1 // B2
                    | GPIO_MODER_MODER10_1 // A
                    | GPIO_MODER_MODER11_1 // B
                    | GPIO_MODER_MODER12_1 // C
                    | GPIO_MODER_MODER13_1); // D

    // set PB0,1,2 for keypad cols(output), PB3,4,5 for keypad(input with pull down resistor)
    GPIOB->MODER &= ~(GPIO_MODER_MODER0_1 //col
                 | GPIO_MODER_MODER1_1
                 | GPIO_MODER_MODER2_1
                 | GPIO_MODER_MODER3_1);
    GPIOB->MODER |= (GPIO_MODER_MODER0_0 //col
                 | GPIO_MODER_MODER1_0
                 | GPIO_MODER_MODER2_0
                 | GPIO_MODER_MODER3_0);

    GPIOB->MODER &= ~(GPIO_MODER_MODER4 //row
                 | GPIO_MODER_MODER5
                 | GPIO_MODER_MODER6
                 | GPIO_MODER_MODER7);

    //pull down resistor
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR4_0;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR4_1;
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR5_0;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR5_1;
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR6_0;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR6_1;
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR7_0;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR7_1;
}

int main(void)
{
    setup_gpio();
    setup_timer6();
    setup_timer3();
    key_function();

	for(;;);
}
