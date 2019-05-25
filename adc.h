//biblioteka obsługi ADC
#include "avr/io.h"

void adc_init();
void adc_start();
uint16_t adc_getData();
uint8_t adc_getDataInPercents();
