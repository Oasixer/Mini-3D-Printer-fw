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
	//waitForEnter();
	zero();
	//manual zero adjustment
	//moveZ(45);
	//wait1Msec(1000);
  scanPaper();
	zero();
	runPrint();
	endProcedure();
}
