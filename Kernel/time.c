#include "include/time.h"
#include "include/naiveConsole.h"

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
	if (ticks %(5*18)==0)
	{
		ncPrint("5 seg");
		ncNewline();
	}
	
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
