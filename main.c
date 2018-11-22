// by Zachariah, Kaelan, Lyndon, Daddy Parth
#include "global.c"
#include "move.c"
#include "start.c"
#include "end.c"
#include "print.c"
#include "buttons.c"
#include "math.c"

task main ()
{
	configureI2C(S4);
	extrude(false);
	wait1Msec(100);
	extrude(true);
	wait1Msec(3000);
	extrude(false);
	//waitForButtonPress();
	zero();
	wait1Msec(1000);
	scanPaper();
	zero();
	runPrint();
	//printSquare(0,0);
	endProcedure();
}
