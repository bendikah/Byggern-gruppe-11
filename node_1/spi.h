#ifndef SPI_H
#define SPI_H

#include <stdint.h>


#define SS 4
#define MOSI 5
#define SCK 7
#define PORTSPI PORTB

void spi_initialize();
char spi_transcieve(char data);
uint8_t spi_recieve();
void spi_transmit(uint8_t data);
void spi_enable(void);
void spi_disable(void);

#endif
