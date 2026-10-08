#include <avr/io.h>
#include <util/delay.h>



int main(void){

    DDRB |= (1 << DDB0); 
    // Configuration in exit mode (1) of Port B's pin 0 
    DDRD &= ~(1 << DDD2); 
    // Configuration in entry mode (0) of Port D's pin 2 
    PORTD |= (1 << PORTD2); 
    // Turn on the resistance of the button 1( on pin 2) to neglect pull up effect

    bool s = false; 
    // Flag to save the current state of the led ( up or down)
    int btn_precedent = 0; 
    // Flag to save the state of the btn before: 0 = not pressed, 1 = pressed

    while(1)
    {   
         int btn_now = !(PIND & (1 << PIND2));

        if (btn_now && !btn_precedent) 
        {
            _delay_ms(20); // delay to prevent the rebound effect
            
            btn_precedent = 1; // last button state is
        }

        if (!btn_now && btn_precedent) {
            _delay_ms(20); // delay to prevent the rebound effect
            s = !s; // new state of the led

            if (s) 
                PORTB |= (1 << PORTB0);
            else
                PORTB &= ~(1 << PORTB0);
            btn_precedent = 0; 
        }

    }
    return (0);
}
