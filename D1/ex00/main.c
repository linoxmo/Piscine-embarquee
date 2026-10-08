#include <avr/io.h>


#include <avr/io.h>

void delay_half_second(void) {
    uint16_t count = 40000; // Outer loop counter
    uint8_t inner = 25;     // Inner loop counter

    // With 16-bit registers, 'sbiw' (2 cycles) + 'brne' (2 cycles) = 4 cycles/loop.
    // To get 0.5s at 16MHz, we need 8,000,000 cycles.
    // Since 8,000,000 / 4 = 2,000,000,
    // we use an outer 8-bit loop of 40 iterations.
    // 2,000,000 / 40 = 50,000 iterations for the inner 16-bit loop.
    
    uint16_t i_count;
    uint8_t o_count = 40; // Outer loop (40 times)

    asm volatile (
        "outer_loop%=:\n\t"
        "ldi %A0, 50000 & 255\n\t" // Load low byte of 50000
        "ldi %B0, 50000 >> 8\n\t"  // Load high byte of 50000
        "inner_loop%=:\n\t"
        "sbiw %A0, 1\n\t"          // 2 cycles
        "brne inner_loop%=\n\t"    // 2 cycles (1 if final)
        "dec %1\n\t"               // 1 cycle
        "brne outer_loop%=\n\t"    // 2 cycles
        : "=&w" (i_count), "+r" (o_count)
    );
}

int main(void) {
    DDRB |= (1 << PB1); // Set PB1 as output
    
    while(1) {
        delay_half_second();
        PORTB ^= (1 << PB1); // Toggle LED
    }
}
