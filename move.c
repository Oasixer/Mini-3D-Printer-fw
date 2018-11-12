#include<global.c>
#include<EV3Servo-lib-UW.c>

float motorPower (float velocity)
{
	const float slope = 1, offset = 0, exponent = 1;
	if (velocity < 0)
		return -slope*pow(abs(velocity), exponent) + offset;
	else
		return slope*pow(abs(velocity), exponent) + offset;
}

void moveXY (float xTarget, float yTarget)
{
	xCur=nMotorEncoder[motorX]*ENC_TO_MM;
	yCur=nMotorEncoder[motorY]*ENC_TO_MM;
	xTar=xTarget;
	yTar=yTarget;
	deX = xTar-xCur;
	deY = yTar-yCur;
	if (abs(deX)> TOLERANCE)
	{
		moX = motorPower(VELOCITY* deX /sqrt(deX*deX+deY*deY));
		step=1.5;//DEBUG
		if (deX<0)
			moX*=-1;
		motor[motorX] = moX;
	}
	if (abs(deY)> TOLERANCE)
	{
		step=1.5;//DEBUG
		moY=motorPower(VELOCITY*deY/sqrt(deX*deX+deY*deY));
		if (deY<0)
			moY*=-1;
		motor[motorY] = moY;
	}
	while (abs(xTar - xCur) > TOLERANCE || abs(yTar - yCur) > TOLERANCE){
		xCur=nMotorEncoder[motorX]*ENC_TO_MM;
		yCur=nMotorEncoder[motorY]*ENC_TO_MM;
		if (abs(xTar - xCur)<TOLERANCE)
		{
			motor[motorX] = 0;
			moX=0;
		}
		if (abs(yTarget - yCur)<TOLERANCE)
		{
			motor[motorY] = 0;
			moY=0;
		}
	}
	motor[motorX]=0;
	moX=0;
	motor[motorY]=0;
	moY=0;
}

void moveZ (float zTarget)
{
	float zCur = nMotorEncoder[motorZ1]*ENC_TO_MM;
	int direction = 1;
	if (zTarget < zCur)
		direction = -1;
	motor[motorZ1] = motor[motorZ2] = 100*direction;
	while(zTarget > zCur*direction)
	{
		zCur = nMotorEncoder[motorZ1]*ENC_TO_MM;
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
