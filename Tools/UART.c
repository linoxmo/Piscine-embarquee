#include "UART.h"

char uart_rx(void)
{
    // Wait for data to be received (RXC0 bit becomes 1)
    while (!(UCSR0A & (1 << RXC0)))
        ;
    return UDR0;
}

void uart_tx(char c) {
    // Wait for empty transmit buffer (UDRE0 bit becomes 1 when ready)
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    
    // Put data into buffer, sends the data
    UDR0 = c;
}

void uart_printstr(const char* str)
{
    // Write a full null-terminated string
    while (*str) {
        uart_tx(*str);
        str++;
    }
}
