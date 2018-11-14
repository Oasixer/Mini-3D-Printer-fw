// by Zachariah, Kaelan, Lyndon, Daddy Parth
#include "global.h"
#include<move.c>
#include<start.c>
#include<print.c>
#include<buttons.c>

task main ()
{
configureI2C(S4);
waitForButtonPress();
zero();
scanPaper();
waitForButtonPress();
zero();
runPrint();
}
