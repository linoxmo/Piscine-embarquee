#include <util/delay.h>
#include "Timer0.h"
#include "Timer2.h"
#include "LED.h"

void init_setup(void) {
    init_RGB();
    initiate_FastPWM_Dual_Timer0((1 << CS01) | (1 << CS00));
    initiate_FastPWM8_Timer2((1 << CS22));
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {
    OCR0B = r;  
    OCR0A = g;  
    OCR2B = b;  
}

Color_t wheel(uint8_t wheel_pos) {
    Color_t c;
    wheel_pos = 255 - wheel_pos;
    
    if (wheel_pos < 85) {
        c.r = 255 - wheel_pos * 3;
        c.g = 0;
        c.b = wheel_pos * 3;
    } else if (wheel_pos < 170) {
        wheel_pos -= 85;
        c.r = 0;
        c.g = wheel_pos * 3;
        c.b = 255 - wheel_pos * 3;
    } else {
        wheel_pos -= 170;
        c.r = wheel_pos * 3;
        c.g = 255 - wheel_pos * 3;
        c.b = 0;
    }
    return c;
}

int main(void) {
    init_setup();
    
    uint8_t i = 0;
    Color_t current_color;

    while (1) {
        current_color = wheel(i);
        set_rgb(current_color.r, current_color.g, current_color.b);
        _delay_ms(20);
        i++;
    }
    
    return 0;
}
