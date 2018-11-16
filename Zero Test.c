/*

Group 414
3D Printer
Zero Test
Nov 16, 2018

*/

#include "start.c"
#include "move.c"

task main()
{
	waitForEnter();
	zero(TOUCH_Y, TOUCH_Z, 50);
}