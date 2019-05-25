
#define F_CPU 16000000UL

#define _BV(A) (1<<A)

#include "st7565-2.h"
#include "avr/io.h"
#include "util/delay.h"
#include "string.h"
#include "spi.h"


#define NR_OF_PAGES 8


static uint8_t buffer[1024];



void st7565_clear(){
	memset(buffer,WHITE,1024);
}
void st7565_fill(uint8_t color){
	memset(buffer,color,1024);
}

void st7565_drawPixel(uint8_t x, uint8_t y, uint8_t color){
	 if (x > ST7565_WIDTH || y > ST7565_HEIGHT)
	    return;
	  if (color == 0)
	    buffer[x + (y / 8) * ST7565_WIDTH] |= (1 << (y % 8));
	  if (color == 1)
	    buffer[x + (y / 8) * ST7565_WIDTH] &= ~(1 << (y % 8));
}


static void set_pageAddress(uint8_t address){
	address&=0x0F;
	st7565_writeCommand(ST7565_PAGE_ADDRESS_SET | address);
}

static void set_columnAddress(uint8_t address){
	address &= 0x7F;
	st7565_writeCommand(ST7565_COLUMN_ADDRESS_SET_MSB | (address >> 4));
	st7565_writeCommand(ST7565_COLUMN_ADDRESS_SET_LSB | (address & 0x0F));
}

void st7565_display(){
	for (uint8_t page = 0; page < NR_OF_PAGES ; page++){
	set_columnAddress(0);
	set_pageAddress(page);
	for (uint8_t i=0; i<ST7565_WIDTH; i++)
		st7565_writeData(buffer[page*128+i]);
	}
}


void st7565_init(){
	ST7565_DDR |= _BV(A0_PIN) | _BV(RST_PIN) | _BV(CS_PIN);
	st7565_reset();
	st7565_writeCommand(ST7565_LCD_BIAS_1_DIV_6_DUTY33);
	st7565_writeCommand(ST7565_ADC_NORMAL);
	st7565_writeCommand(ST7565_REVERSE_SCAN_DIRECTION);
	st7565_writeCommand(ST7565_VOLTAGE_RESISTOR_RATIO_7);

	st7565_setContrast(20);
	st7565_writeCommand(ST7565_POWER_CTRL_ALL_ON);
	st7565_writeCommand(ST7565_BOOSTER_RATIO_SET);
	st7565_writeCommand(ST7565_BOOSTER_RATIO_2X_3X_4X);

	st7565_writeCommand(ST7565_DISPLAY_NORMAL);
	st7565_writeCommand(ST7565_START_LINE_SET);
	st7565_writeCommand(ST7565_DISPLAY_ON);
}


void st7565_setContrast(uint8_t contrast){
	st7565_writeCommand(ST7565_ELECTRONIC_VOLUME_MODE_SET);
	st7565_writeCommand(contrast);
}


void st7565_writeCommand(uint8_t command){
	ST7565_PORT &= ~_BV(CS_PIN);
	ST7565_PORT &= ~_BV(A0_PIN);
	spi_readWrite(command);
	ST7565_PORT |= _BV(CS_PIN);
}
void st7565_writeData(uint8_t data){
	ST7565_PORT &= ~_BV(CS_PIN);
	ST7565_PORT |= _BV(A0_PIN);
	spi_readWrite(data);
	ST7565_PORT |= _BV(CS_PIN);
}

void st7565_reset(){
	ST7565_PORT &= ~_BV(RST_PIN);
	_delay_ms(50);
	ST7565_PORT |= _BV(RST_PIN);
	_delay_us(100);
}
