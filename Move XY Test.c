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
	nMotorEncoder[motorX] = 0;
	nMotorEncoder[motorY] = 0;
	for (int count = 0; count < 10; count++)
	{
		//extrude(false);
		moveXY(20, 30);
		wait1Msec(1000);

		//extrude(true);
		moveXY(0,0);
		wait1Msec(1000);
	}
}
