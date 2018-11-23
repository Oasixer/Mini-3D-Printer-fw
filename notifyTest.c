// by Zachariah, Kaelan, Lyndon, Daddy Parth
#include "global.c"
#include "move.c"
#include "start.c"
#include "end.c"
#include "buttons.c"
#include "math.c"

task main(){
	zero();
	endProcedure();
	for (int i = 0; i < 3; i++)
	{
		notifyUser(440, 30, ledGreenFlash);
		wait1Msec(5000);
		notifyUser(587, 30, ledRedPulse);
		wait1Msec(5000);
	}
}
