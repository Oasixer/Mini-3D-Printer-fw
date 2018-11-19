// by Zachariah, Kaelan, Lyndon, Daddy Parth
#include "global.c"
#include "move.c"
#include "start.c"
#include "print.c"
#include "buttons.c"
#include "math.c"

task main ()
{
	configureI2C(S4);
	extrude(false);
	//waitForButtonPress();
	zero();
	wait1Msec(3000);
	scanPaper();
	runPrint();
	//printSquare(0,0);
}
