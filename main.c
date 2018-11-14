// by Zachariah, Kaelan, Lyndon, Daddy Parth
#include<global.c>
#include<move.c>
#include<start.c>
#include<print.c>
#include<buttons.c>

task main ()
{
waitForButtonPress();
zero();
scanPaper();
waitForButtonPress();
zero();
runPrint();
}
