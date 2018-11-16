//servo testing
#include "EV3Servo-lib_UW.c"
#include "move.c"
task main(){
  //setServoPosition(int ev3Port, int servo_number, int position);
  //setServoPosition(S4, 1, 25);// extrude on
  //setServoPosition(S4, 1, 0);//extrude off

	//testing servo
	for (int i = 0; i < 25; i++)
	{
		setServoPosition(S4, 1, i);
		wait1MSec(1000);
	}

	setServoPosition(S4, 1, 0);
	//testing function calls
	extrude(1);
	wait1MSec(1000);
	extrude(0);
}