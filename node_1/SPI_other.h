/*
 * SPI.h
 *
 * Created: 15.10.2017 17:02:34
 *  Author: thomasnl
 */ 


#ifndef SPI_H_
#define SPI_H_


void SPI_init();

void SPI_MasterTransmit(char cData);

char SPI_MasterReceive();



#endif /* SPI_H_ */