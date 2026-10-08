#include <avr/io.h>
#include <util/delay.h>

void ft_bin(int count) {
    // Bit 0 goes to PORTB0
    if (count & (1 << 0)) PORTB |= (1 << PORTB0); else PORTB &= ~(1 << PORTB0);
    
    // Bit 1 goes to PORTB1
    if (count & (1 << 1)) PORTB |= (1 << PORTB1); else PORTB &= ~(1 << PORTB1);
    
    // Bit 2 goes to PORTB2
    if (count & (1 << 2)) PORTB |= (1 << PORTB2); else PORTB &= ~(1 << PORTB2);
    
    // Bit 3 jumps directly to PORTB4
    if (count & (1 << 3)) PORTB |= (1 << PORTB4); else PORTB &= ~(1 << PORTB4);
}

int main(void){

    DDRB |= (1 << DDB0) |  (1 << DDB1) | (1 << DDB2) | (1 << DDB4); 
    // Configuration in exit mode (1) of Port B's pin 0 , 1, 2 ,4
    DDRD &= ~(1 << DDD2) & ~(1 << DDD4);  
    // Configuration of Port D's 2 and 4 pins in entree mode 
    PORTD |= (1 << PORTD2) | (1 << PORTD4); 
    // For pull up effect

    
    int i = 0;  
    // the iterator
    int btn1_precedent = 0; 
    int btn2_precedent = 0; 
    // Flag to save the state of the btn before: 0 = not pressed, 1 = pressed

    while(1)
    {   
        int btn1_now = !(PIND & (1 << PIND2));
        int btn2_now = !(PIND & (1 << PIND4));
        
        //First Button
        if (btn1_now && !btn1_precedent) 
        {
            _delay_ms(20);
            
            btn1_precedent = 1;
        }
        
        if (!btn1_now && btn1_precedent) 
        {    
            _delay_ms(20); 
            if (i < 15)
                i += 1;  
            // i is iterate when pressed
            btn1_precedent = 0;
        }
        // Second Bouton
        if (btn2_now && !btn2_precedent) 
        {
            _delay_ms(20);
            
            btn2_precedent = 1;
        }
        if (!btn2_now && btn2_precedent) 
        {
            _delay_ms(20); 
            if (i > 0)
                i = i - 1;
            // i is iterate when pressed
            btn2_precedent = 0;
        }
        ft_bin(i);
    }
    return 0;
    }
