#include <avr/io.h>

void delay_half_second(void) {
    volatile uint32_t i = 380952UL; 

    /*
    Charge the 4 bytes in the registre : lds *4 cycles
    Copi the 4 bytes for decrementation : mov * 4 cycles
    Soustraction with saving on 32 bits : sbci * 4 cycles
    Write the new result : sts * 4 cycles
    Test if the value == to 0  3 * or ( combine Bite 0 with 1, 2, 3)
    If result not true,do the loop agin, brne *(1/2) cylces 
    */
    
    while (i--) {
        ; 
    }
}

int main(void) {
    DDRB |= (1 << PB1); // Set PB1 as output
    
    while(1) {
        delay_half_second();
        PORTB ^= (1 << PB1); // Toggle LED
    }
}
