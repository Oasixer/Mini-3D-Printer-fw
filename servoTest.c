//servo testing
#include "EV3Servo-lib-UW.c"
task main(){
  //setServoPosition(int ev3Port, int servo_number, int position);
  //setServoPosition(S4, 1, 25);// extrude on
  //setServoPosition(S4, 1, 0);//extrude off

	//testing servo
	for (int i = 0; i < 25; i++)
	{
		setServoPosition(S4, 1, i);
		wait1Msec(1000);
	}
}
