// by Zachariah, Kaelan, Lyndon, Daddy Parth
#include "global.c"
#include "move.c"
#include "buttons.c"
#include "math.c"

void notifyUser(int frequency, int timeSound, TEV3LEDPatterns led)
{
	playTone(frequency, timeSound);
	setLEDColor(led);
}

task main(){
	for (int i = 0; i < 10; i++)
	{
		notifyUser(784, 30, LED_GREEN_FLASH);
	}
}