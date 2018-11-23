// by Zachariah, Kaelan, Lyndon, Daddy Parth
#include "global.c"
#include "move.c"
#include "buttons.c"
#include "math.c"

#ifndef END_C
#define END_C

void notifyUser(int frequency, int timeSound, TEV3LEDPatterns led)
{
	playTone(frequency, timeSound);
	setLEDColor(led);
}

void endProcedure()
{
	moveZ(Z_MAX);

	notifyUser(440, 30, ledOrangePulse);

	notifyUser(440, 30, ledRedFlash);

	wait10Msec(COOL_DOWN_TIME);

	notifyUser(440, 30, ledGreenFlash);

	waitForEnter();
}

#endif
