#include "global.c"

void waitForEnter(){
	while (!getButtonPress(buttonEnter)){}
	while (getButtonPress(buttonEnter)){}
}
