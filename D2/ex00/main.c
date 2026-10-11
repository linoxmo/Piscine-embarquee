#define F_CPU 16000000UL    
#define UART_BAUDRATE 115200

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void uart_init(void) {
    // Calculate UBRR value based on F_CPU and UART_BAUDRATE for standard asynchronous mode
    uint16_t ubrr_value = ((F_CPU / (8UL * UART_BAUDRATE)) - 1);
    
    // Set baud rate registers (High and Low)
    UBRR0H = (uint8_t)(ubrr_value >> 8);
    UBRR0L = (uint8_t)(ubrr_value);
    
    UCSR0A |= (1 << U2X0);
    // Enable transmitter (TX)
    UCSR0B |= (1 << TXEN0);

    
    // Set frame format: 8 data bits, no parity, 1 stop bit (8N1)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
} 

void uart_tx(unsigned char c) {
    // Wait for empty transmit buffer (UDRE0 bit becomes 1 when ready)
    while (!(UCSR0A & (1 << UDRE0)));
    
    // Put data into buffer, sends the data
    UDR0 = c;
}

int main(void) {
    // Initialize the UART interface
    uart_init();
    
    while(1) {
        // Send 'Z' over the serial port
        uart_tx('Z');
        
        // Wait 1 second to achieve a 1 Hz frequency
        _delay_ms(1000);
    }
}