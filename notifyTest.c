/*
Group 414
3D Printer
Test for notifying user of finished print
*/

#include "global.c"
#include "move.c"
#include "start.c"
#include "end.c"
#include "buttons.c"
#include "misc.c"

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
