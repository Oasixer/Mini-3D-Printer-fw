/*
Group 414
3D Printer
Servo Test
*/

#include "EV3Servo-lib-UW.c"
#include "move.c"
#include "misc.c"
task main(){
	extrude(0);
	wait1Msec(1000);
	extrude(1);
	wait1Msec(3000);
	extrude(0);
}
