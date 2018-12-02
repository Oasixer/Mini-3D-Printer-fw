#include "global.c"
#include "EV3Servo-lib-UW.c"
#include "misc.c"

#ifndef MOVE_C
#define MOVE_C

float motorPower (float velocity)
{
  //this method is a placeholder for any math needed to convert a velocity in mm/s to the motor power needed to achieve that velocity
  //it happens that for our system, the velocity value is close enough to the motor power to use without scaling.
  return constrain(velocity, -100, 100);
}

void moveXY (float xTarget, float yTarget) //move to a set of absolute coordinates in the x and y axis
{
  float powerX = 0, powerY = 0;
  float xCurrent = nMotorEncoder[motorX] * ENC_TO_MM; //calculate current x and y in mm
  float yCurrent = nMotorEncoder[motorY] * ENC_TO_MM;
  xTarget = -xTarget; // invert x value to account for reversed x axis motor
  float deltaX = xTarget - xCurrent; //calculate the delta between target and current x and y value
  float deltaY = yTarget - yCurrent;

  float deltaTotal = sqrt(deltaX*deltaX + deltaY*deltaY); //calculate the total delta in the x and y plane
  if (!deltaTotal)
    deltaTotal = 0.0001; //account for divide by zero errors
  if (abs(deltaX) > TOLERANCE) //check if the x axis is within tolerance, assign motor power
  {
    powerX = motorPower(VELOCITY * deltaX / deltaTotal);
    motor[motorX] = powerX;
  }
  if (abs(deltaY) > TOLERANCE) //check if the y axis is within tolerance, assign motor power
  {
    powerY = motorPower(VELOCITY * deltaY / deltaTotal);
    motor[motorY] = powerY;
  }
  
  //loop until both the x and y axis are within tolerance.
  //Additionally, do not loop if both motor powers have already been set to 0
  //This fixes the edge case setpoint overshoot that could lead to an infinite loop without movement
  while ((!(abs(deltaX) < TOLERANCE && abs(deltaY) < TOLERANCE))&&(powerX!=0||powerY!=0))
  {
    wait1Msec(20);
    xCurrent = nMotorEncoder[motorX] * ENC_TO_MM;
    yCurrent = nMotorEncoder[motorY] * ENC_TO_MM;
    deltaX = xTarget - xCurrent;
    deltaY = yTarget - yCurrent;

    if (abs(deltaX) < TOLERANCE){ //check if the x axis is within tolerance
      motor[motorX] = 0; 
      powerX=0;
      }

    if (abs(deltaY) < TOLERANCE){ //check if the y axis is within tolerance 
      motor[motorY] = 0;
      powerY=0;
      }

  }
  motor[motorX] = motor[motorY] = 0; //set motor powers to 0 in case the loop exits before setting powers to 0
}

void moveZ (float zTarget) //moves the Z axis to an absolute height in mm 
{
  float zCurrent1 = nMotorEncoder[motorZ1] * Z_ENC_TO_MM; //calculate current height
  float zCurrent2 = nMotorEncoder[motorZ2] * Z_ENC_TO_MM;

  int direction = 1; //check direction
  if (zTarget < zCurrent1)
    direction = -1;
  
  //note: motor Z2 has a slightly lower power to account for the difference in friction between both sides
  motor[motorZ1] = 100 * direction;
  motor[motorZ2] = 95 * direction;

  //loop until the z axis has reached it's target
  while(!(abs(zTarget-zCurrent1) < TOLERANCE && abs(zTarget-zCurrent2) < TOLERANCE))
  {
    zCurrent1 = nMotorEncoder[motorZ1] * Z_ENC_TO_MM;
    zCurrent2 = nMotorEncoder[motorZ2] * Z_ENC_TO_MM;

    if (abs(zCurrent1-zTarget) < TOLERANCE) //check current value against target, zero power when within range
      motor[motorZ1] = 0;

    if (abs(zCurrent2-zTarget) < TOLERANCE)
      motor[motorZ2] = 0;
  }
  motor[motorZ1] = motor[motorZ2] = 0; //set power to zero in case loop exits without doing so
}

void extrude (bool input) //takes commands to start or stop extruding and moves the servo accordingly
{
  wait1Msec(40);
  if (input){
    setServoPosition(S4, 1, -63);//extrude on
  }
  else {
    setServoPosition(S4, 1, -30);//extrude off
  }
  wait1Msec(40);
}

#endif
