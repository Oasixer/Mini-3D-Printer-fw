#include "global.c"

#ifndef BUTTONS_C
#define BUTTONS_C

void waitForEnter(){
	while (!getButtonPress(buttonEnter)){}
	while (getButtonPress(buttonEnter)){}
}

#endif