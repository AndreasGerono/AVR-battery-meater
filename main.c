//Projekt graficznego wskaźnika stanu baterii
//Autor: Andreas Gerono



#define F_CPU 16000000UL

#define _BV(A) (1<<A)


#include "avr/io.h"
#include "stdlib.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "spi.h"
#include "st7565-2.h"
#include "graphicDisplay.h"

#include "adafruit5x7.h"
#include "batteryDrawing.h"
#include "adc.h"
#include "stdio.h"


void timerInit();
void refreshBattery();
volatile _Bool refreshBatteryFlag;


ISR(TIMER1_COMPA_vect){
	refreshBatteryFlag = 1;
}


int main(void) {



Font font1 = {adafruit,ADA_WIDTH,ADA_HEIGHT,BLACK,WHITE}; //nowa czcionka 
display_setFont(&font1);	//ustawienie aktualnej aktywnej czcionki




//funckje inicjalizacji
timerInit();
spi_init();
adc_init();
st7565_init();
sei();


adc_start();
Battery_drawIcon(); //rysowanie ikony baterii




while(1){

	if (refreshBatteryFlag)
		refreshBattery();
	
	
	
	
	
	
	}
}

void timerInit(){
	TIMSK |= _BV(OCIE1A);
	OCR1A = 2000;	//~1.5s
	TCCR1B |= _BV(CS12) | _BV(CS10);
	TCCR1B |= _BV(WGM12);
}


//funckja odświeżajaca bitmapę baterii
void refreshBattery(){
	uint8_t percents = adc_getDataInPercents(); 
	Battery_drawPercents(percents);
	Battery_writePercents(percents);	
	st7565_display();
	adc_start();	//wyzwolenie następnego pomiaru
	refreshBatteryFlag = 0;
}

