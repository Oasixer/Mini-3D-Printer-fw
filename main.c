/*
Group 414
3D Printer
Main file, main task
*/
#include "global.c"
#include "move.c"
#include "start.c"
#include "end.c"
#include "print.c"
#include "misc.c"

task main ()
{
  configureI2C(S4);
  waitForEnter();
  zero();
  scanPaper();
  runPrint();
  endProcedure();
}
