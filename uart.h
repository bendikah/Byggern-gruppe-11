#ifndef UART_H
#define UART_H

void USART_Init(unsigned int ubrr );
void USART_Transmit(char data);
unsigned int USART_Receive(void);


#endif
