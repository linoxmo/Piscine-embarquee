#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

#define F_CPU 16000000UL 
#define UART_BAUDRATE 115200
#define LEN (str) (sizeof(str))
void uart_init(void) {
    // Calculate UBRR value based on F_CPU and UART_BAUDRATE for standard asynchronous mode
    uint16_t ubrr_value = (F_CPU / 8UL / UART_BAUDRATE - 1);
    
    // Set baud rate registers (High and Low)
    UBRR0H = (unsigned char)(ubrr_value >> 8);
    UBRR0L = (unsigned char)(ubrr_value);
    
    UCSR0A |= (1 << U2X0);
    // Enable transmitter (TX)
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    
    // Set frame format: 8 data bits, no parity, 1 stop bit (8N1)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

char uart_rx(void)
{
    unsigned char status, resh, resl;
    while (! (UCSR0A & (1<<RXC0)))
        ;
    return UDR0;
}

void  uart_tx(char c) {
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

char *ft_strcat(char *s1, char s2)
{
    int i = 0;
    char *s3 = malloc(strlen(s1) + 2);
    while(s3[i] && s1[i])
    {
        s3[i] = s1[i];
        i++;
    }
    s3[i] = s2;
    i++;
    s3[i]= '\0';
    return s3;
}

int main(){
    char username[7] = "spectre";
    char password[9] = "cassoulet";
    char c;
    char *temp = strdup("");
    int i = 1;
    int j = 0 ;

    uart_init(); // init the transmittion/receiver
    uart_printstr("Enter your login:\n\r");
    while(i) {
        while(strlen(temp) < 7 )
        {
            c = uart_rx();
            uart_tx(c);
            j++;
            temp = ft_strcat(temp, c);
        }
        uart_printstr("\nYour login:\n\r");
        i = 0;
    }
}