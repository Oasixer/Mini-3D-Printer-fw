// Servo tests

#include "EV3Servo-lib_UW.c"

task main(){
  //setServoPosition(int ev3Port, int servo_number, int position);
  setServoPosition(S4, 1, 25);// extrude on
  setServoPosition(S4, 1, 0);//extrude off
}
