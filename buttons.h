#include "global.c"

void waitForButtonPress(){
	while (!getButtonPress(buttonEnter)){}
	while (getButtonPress(buttonEnter)){}
}
