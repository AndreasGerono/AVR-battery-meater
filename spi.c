

#include "spi.h"
#define _BV(A) (1<<A)


void spi_init(){
	DDRB |= _BV(PB7) | _BV(PB5) | _BV(PB4); //mosi/sck/cs jako wyjście
	SPCR |= _BV(SPE) | _BV(MSTR) | _BV(CPOL) | _BV(CPHA); //tryb z przesunięciem fazy
	
}

//funckja zapisu/odczytu z SPI
uint8_t spi_readWrite(uint8_t data){
	SPDR=data;                    
	while(!(SPSR & (1<<SPIF)));   
	return SPDR;     
}
