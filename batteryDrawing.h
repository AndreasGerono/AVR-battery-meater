//biblioteka obsługi rysowania baterii

#include "stdint.h"

#define BATTERY_POSITION_X 10
#define BATTERY_POSITION_Y 15
#define BATTERY_TEXT_POSITION_X 0
#define BATTERY_TEXT_POSITION_Y 0

void Battery_drawPercents(uint8_t);
void Battery_writePercents(uint16_t);
void Battery_drawIcon();


