//servo testing
#include "EV3Servo-lib-UW.c"
#include "move.c"
task main(){
  //setServoPosition(int ev3Port, int servo_number, int position);
  //setServoPosition(S4, 1, 25);// extrude on
  //setServoPosition(S4, 1, 0);//extrude off

	//testing servo
/*	for (int count = 0; count < 5; count++)
	{
		setServoPosition(S4, 1, 0);
		wait1Msec(1000);
		setServoPosition(S4, 1, 60);
		wait1Msec(1000);
	}
*///for (int i = 0; i < 50; i++)
	//{
	//	setServoPosition(S4, 1, i);
	//	wait1Msec(100);
	//}

	//for (int i = 0; i < 50; i++)
	//{
	//	setServoPosition(S4, 1, 50-i);
	//	wait1Msec(100);
	//}
	extrude(0);
	wait1Msec(1000);
	extrude(1);
}
