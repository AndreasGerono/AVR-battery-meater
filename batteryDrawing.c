
#include "batteryDrawing.h"
#include "batteryBitmap.h"
#include "graphicDisplay.h"
#include "stdio.h"


//nowa struktura bitmapy
static Bitmap battery = {batteryData,BATTERY_WIDTH,BATTERY_HEIGHT,BLACK,WHITE};


//definicja kresek baterii
#define BAR_NUMBER 10
#define BAR_WIDTH (BATTERY_CAPACITY/BAR_NUMBER)
#define BAR_HEIGHT (BATTERY_HEIGHT-BATTERY_LINE_WIDTH*2 -1)
#define BAR_MARGIN 1


//funckja czyszcząca środek baterii
static void clearBattery(){
	display_fillRect(BATTERY_POSITION_X+BATTERY_LINE_WIDTH,
				BATTERY_POSITION_Y+BATTERY_LINE_WIDTH,BATTERY_CAPACITY,BAR_HEIGHT, WHITE);
}


//funkja rysująca kreski baterii
void Battery_drawPercents(uint8_t percent){
	clearBattery();
	if (percent){
		uint8_t bars = 1+BAR_NUMBER*(percent-1)/100;
	for (uint8_t i=0; i<bars; i++ )
		display_fillRect(BATTERY_POSITION_X+BATTERY_LINE_WIDTH+BAR_MARGIN+i*BAR_WIDTH,
				BATTERY_POSITION_Y+BATTERY_LINE_WIDTH+BAR_MARGIN,BAR_WIDTH-2*BAR_MARGIN,BAR_HEIGHT-2*BAR_MARGIN, BLACK);
	}
}


//funkcja pisząca procenty baterii
void Battery_writePercents(uint16_t percents){
	char text[20];
	sprintf(text," Battery: %3u%% ", percents);
	display_setCursor(BATTERY_TEXT_POSITION_X,BATTERY_TEXT_POSITION_Y);
	display_writeText(text);
}

//funckja rysująca bitmapę baterii
void Battery_drawIcon(){
	display_drawBitmap(BATTERY_POSITION_X,BATTERY_POSITION_Y,&battery);
}


