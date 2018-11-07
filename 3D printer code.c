// by Zachariah Mears
const int velocity = 25; //mm/s 200/8
const float encoderCountPermm = 180/PI*4;
const float TOLERANCE = 2;
int motorX = motorA, motorY = motorB, motorZ = motorC, motorE = motorD;


float motorPower (float velocity);
void moveXY (float xTarget, float yTarget)
{
	float deltaX = xTarget - nMotorEncoder[motorX];
	float deltaY = yTarget - nMotorEncoder[motorY];
	motor[motorX] = motorPower(velocity*encoderCountPermm*deltaX/sqrt(pow(deltaX,2) + pow(deltaY,2)));
	motor[motorY] = motorPower(velocity*encoderCountPermm*deltaY/sqrt(pow(deltaX,2) + pow(deltaY,2)));

	while (abs(xTarget - nMotorEncoder[motorX])>TOLERANCE || abs(yTarget - nMotorEncoder[motorY])>TOLERANCE)
	{
		if (abs(xTarget - nMotorEncoder[motorX])>TOLERANCE)
		{
			motor[motorX] = 0;
		}
		if (abs(yTarget - nMotorEncoder[motorY])>TOLERANCE)
		{
			motor[motorY] = 0;
		}
	}
}

task main ()
{


}


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
