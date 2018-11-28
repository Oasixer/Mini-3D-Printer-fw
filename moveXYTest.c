/*
Group 414
3D Printer
moveXY Test
*/

#include "start.c"
#include "move.c"

task main()
{
	nMotorEncoder[motorX] = 0;
	nMotorEncoder[motorY] = 0;
  //move around and test the extruder
	for (int count = 0; count < 10; count++) //run 10 times
	{
		extrude(false);
		moveXY(20, 30);
		wait1Msec(1000);

		extrude(true);
		moveXY(0,0);
		wait1Msec(1000);

		extrude(false);
		moveXY(-20, 0);
		wait1Msec(1000);
	}
}
