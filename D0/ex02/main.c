#include <avr/io.h>


int main(void){

    DDRB |= (1 << DDB0); 
    // Configuration in exit mode (1) of Port B's pin 0 
    DDRD &= ~(1 << DDD2); 
    // Configuration in entry mode (0) of Port D's pin 2 
    PORTD |= (1 << PORTD2); 
    // Turn on the resistance of the button 1( on pin 2) to neglect pull up effect
    
    while(1)
    {   
        // Read the Button states with PIND 
        if (!(PIND & (1 << PIND2))) // ==  If the button is pressed
            PORTB |= (1 << PORTB0);
        else
            PORTB &= ~(1 << PORTB0);
        
    }
    return (0);
}