#define F_CPU 16000000UL    
#define UART_BAUDRATE 115200

#include <avr/io.h>
#include <avr/interrupt.h>

void uart_init(void) {
    // Calculate UBRR value based on F_CPU and UART_BAUDRATE for standard asynchronous mode
    uint16_t ubrr_value = (F_CPU / 8UL / UART_BAUDRATE - 1);
    
    // Set baud rate registers (High and Low)
    UBRR0H = (unsigned char)(ubrr_value >> 8);
    UBRR0L = (unsigned char)(ubrr_value);
    
    UCSR0A |= (1 << U2X0);
    // Enable transmitter (TX)
    UCSR0B |= (1 << TXEN0);

    
    // Set frame format: 8 data bits, no parity, 1 stop bit (8N1)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void timer_init(void){
    TIMSK1 |= (1 << OCIE1A);
    OCR1A = (F_CPU / 1024) * 2 - 1;
    // Ticks = Periode * (FCPU / Prescaler) -1
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
    // O
    
}

void uart_tx(unsigned char c) {
    // Wait for empty transmit buffer (UDRE0 bit becomes 1 when ready)
    while (!(UCSR0A & (1 << UDRE0)));
    
    // Put data into buffer, sends the data
    UDR0 = c;
}

void uart_printstr(const char* str)
{
        // write a full string
        while(*str){
            uart_tx(*str);
            str ++;
        }
}

void TIMER1_COMPA_vect(void){
    uart_printstr("Hello World!\n\r");
    SREG |= (1<<7);
    // The interruption is forced once
}

int main(void) {
    // Initialize the UART interface
    SREG &= ~(1 <<7 );
    uart_init();
    // uart_printstr("\n\r=== DEMARRAGE DU MICROCONTROLEUR ===\n\r");  Proof that I dont break the board
    timer_init();
    SREG |= (1 <<7 ); // force for the first time to create a loop
    while(1) {
        }
                
    }


    /* screen /dev/ttyUSB0 et pkill screen to stop the screen*/