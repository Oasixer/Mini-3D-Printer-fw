#include "global.c"

#IFNDEF BUTTONS_C
#DEFINE BUTTONS_C

void waitForEnter(){
	while (!getButtonPress(buttonEnter)){}
	while (getButtonPress(buttonEnter)){}
}

#ENDIF