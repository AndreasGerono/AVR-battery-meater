//biblioteka obsługi interfejsu SPI

#include "avr/io.h"
#include "stdlib.h"

void spi_init();
uint8_t spi_readWrite(uint8_t);
