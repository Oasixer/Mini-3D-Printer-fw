/*

Group 414
3D Printer
Scan Test
Nov 16, 2018

*/

#include "start.c"
#include "move.c"

task main()
{
	for (int count = 0; count < 10; count++)
	{
		moveXY(10, 10);
		wait1Msec(1000);
		moveXY(0,0);
		wait1Msec(1000);
	}
}