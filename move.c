#include "global.c"
#include "EV3Servo-lib-UW.c"
#include "math.c"

#ifndef MOVE_C
#define MOVE_C

void display(int line, float x, float y)
{
	displayString(line, "(%f, %f)", x, y);
}

float motorPower (float velocity)
{
	const float slope = 1, offset = 0, exponent = 1;
	// if (velocity < 0)
		// return -slope * pow(abs(velocity), exponent) + offset;
	// else
	//return


	return constrain(velocity, -100, 100);
}

void moveXY (float xTarget, float yTarget)
{
	float powerX = 0, powerY = 0;

	float xCurrent = nMotorEncoder[motorX] * ENC_TO_MM;
	float yCurrent = nMotorEncoder[motorY] * ENC_TO_MM;

	// invert x value to match hardware setup
	xTarget = -xTarget;
	float deltaX = xTarget - xCurrent;
	float deltaY = yTarget - yCurrent;

	float deltaV = sqrt(deltaX*deltaX + deltaY*deltaY);
	if (!deltaV)
		deltaV = 0.2;
	if (abs(deltaX) > TOLERANCE)
	{
		powerX = motorPower(VELOCITY * deltaX / deltaV);
		motor[motorX] = powerX;
	}
	if (abs(deltaY) > TOLERANCE)
	{
		powerY = motorPower(VELOCITY * deltaY / deltaV);
		motor[motorY] = powerY;
	}

	while ((!(abs(deltaX) < TOLERANCE && abs(deltaY) < TOLERANCE))&&(powerX!=0||powerY!=0))
	{
		wait1Msec(20);
		xCurrent = nMotorEncoder[motorX] * ENC_TO_MM;
		yCurrent = nMotorEncoder[motorY] * ENC_TO_MM;
		deltaX = xTarget - xCurrent;
		deltaY = yTarget - yCurrent;

		if (abs(deltaX) < TOLERANCE){
			motor[motorX] = 0;
			powerX=0;
			}

		if (abs(deltaY) < TOLERANCE){
			motor[motorY] = 0;
			powerY=0;
			}

	}
	motor[motorX] = motor[motorY] = 0;
}

void moveZ (float zTarget)
{
	float zCurrent1 = nMotorEncoder[motorZ1] * Z_ENC_TO_MM;
	float zCurrent2 = nMotorEncoder[motorZ2] * Z_ENC_TO_MM;

	int direction = 1;
	if (zTarget < zCurrent1)
		direction = -1;

	motor[motorZ1] = 100 * direction;
	motor[motorZ2] = 95 * direction;
	while(!(abs(zTarget-zCurrent1) < TOLERANCE && abs(zTarget-zCurrent2) < TOLERANCE))
	{
		zCurrent1 = nMotorEncoder[motorZ1] * Z_ENC_TO_MM;
		zCurrent2 = nMotorEncoder[motorZ2] * Z_ENC_TO_MM;

		if (abs(zCurrent1-zTarget) < TOLERANCE)
			motor[motorZ1] = 0;

		if (abs(zCurrent2-zTarget) < TOLERANCE)
			motor[motorZ2] = 0;
	}
	motor[motorZ1] = motor[motorZ2] = 0;
}

void extrude (bool input)
{
	wait1Msec(40);
	if (input){
		// values are for Zach's servo
		setServoPosition(S4, 1, 0);// extrude on
	}
	else {
		setServoPosition(S4, 1, 90);//extrude off
	}
	wait1Msec(40);
}

#endif
