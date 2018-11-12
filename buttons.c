#include<globals.c>

void waitForButtonPress(){
	while (!getButtonPress(buttonEnter)){}
}

