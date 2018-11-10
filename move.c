#include<global.c>
#include<EV3Servo-lib-UW.c>

float motorPower (float velocity)
{
	const float slope = 1, offset = 0, exponent = 1;
	if (velocity < 0)
	{
	return -slope*pow(abs(velocity), exponent) + offset;
	}
	else
	{
		return slope*pow(abs(velocity), exponent) + offset;
	}
}

void moveXY (float xTarget, float yTarget)
{
	float xCur=nMotorEncoder[motorX]*ENCTOMM;
	float yCur=nMotorEncoder[motorY]*ENCTOMM;
	xTar=xTarget;
	yTar=yTarget;
	float deltaX = xTarget-xCur;
	deX=deltaX;
	float deltaY = yTarget-yCur; //AHHHH remember to fix indeterminate case below when deltaX or deltaY==0
	deY=deltaY;
	if (abs(deltaX)> TOLERANCE)
	{
		moX = motor[motorX] = motorPower(velocity* deltaX /sqrt(deltaX*deltaX+deltaY*deltaY));
	}
	if (abs(deltaY)> TOLERANCE)
	{
		moY= motor[motorY] = motorPower(velocity*deltaY/sqrt(deltaX*deltaX+deltaY*deltaY));
	}
	while (abs(xTarget - xCur) > TOLERANCE || abs(yTarget - yCur) > TOLERANCE){
		xCur=nMotorEncoder[motorX]*ENCTOMM;
		yCur=nMotorEncoder[motorY]*ENCTOMM;
		if (abs(xTarget - xCur)<TOLERANCE)
		{
			motor[motorX] = 0;
		}
		if (abs(yTarget - yCur)<TOLERANCE)
		{
			motor[motorY] = 0;
		}
	}
	motor[motorX]=0;
	motor[motorY]=0;
}

void moveZ (float zTarget)
{
	float zCur = nMotorEncoder[motorZ1]*ENCTOMM;
	int direction = 1;
	if (zTarget < zCur)
		direction = -1;
	motor[motorZ1] = motor[motorZ2] = 100*direction;
	while(zTarget > zCur*direction)
	{
		zCur = nMotorEncoder[motorZ1]*ENCTOMM;
	}
	motor[motorZ1] = motor[motorZ2] = 0;
}


void extrude (bool input)
{
	if (input){
		setServoPosition(S4, 1, 25);// extrude on
	}
	else {
		setServoPosition(S4, 1, 0);//extrude off
	}
}
