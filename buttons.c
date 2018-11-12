#include<global.c>

void waitForButtonPress(){
	while (!getButtonPress(buttonEnter)){}
}

