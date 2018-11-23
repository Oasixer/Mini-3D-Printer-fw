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

void endProcedure()
{
	moveZ(Z_MAX);

	notifyUser(784, 30, ledOrangePulse);

	notifyUser(784, 30, ledRedFlash);

	wait10Msec(COOL_DOWN_TIME);

	notifyUser(784, 30, ledGreenFlash);

	waitForEnter();
}
