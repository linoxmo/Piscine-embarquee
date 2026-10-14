#ifndef UART_H
#define UART_H

#define uart_init_Double_speed(ubrr_value) \
do{\
    UBRR0H = (unsigned char)(ubrr_value >> 8);\
    UBRR0L = (unsigned char)(ubrr_value);\
    UCSR0A |= (1 << U2X0);\
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);\
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);\
}while(0)
// Calculate UBRR value based on F_CPU and UART_BAUDRATE for standard asynchronous mode
// Set baud rate registers (High and Low)
// Enable transmitter (TX)
// Set frame format: 8 data bits, no parity, 1 stop bit (8N1)

char uart_rx(void);
void uart_tx(char c);
void uart_printstr(const char* str);

#endif