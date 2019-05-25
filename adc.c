#include "adc.h"
#include "avr/interrupt.h"

#define ADC_MAX 1023UL

static volatile uint16_t adcVal;

static void adc_stop(){
	ADCSRA &= ~_BV(ADSC);
}


//przerwanie od zakończenia pomiaru adc
ISR(ADC_vect){
	adcVal = ADC;
}


//inicjalizacja adc w trybie jednego pomiaru z przerwaniem
void adc_init(){
	ADMUX |= _BV(REFS0) | _BV(REFS1); //wewnętrzne napięcie referencyjne
	ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);	//preskaler x64
	
	ADCSRA |= _BV(ADIE);	//włączenie przerwania
	ADCSRA |= _BV(ADEN); //włączenie przetwornika
}




void adc_start(){
	ADCSRA |= _BV(ADSC); 
}

uint16_t adc_getData(){
	return adcVal;
}

uint8_t adc_getDataInPercents(){
	return ((uint32_t)adcVal*100)/ADC_MAX;
}
