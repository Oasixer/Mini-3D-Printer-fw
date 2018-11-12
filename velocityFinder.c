// velocity finder by Zachariah Mears
// used to calibrate motorPower function
#include<constants.c>

int testCases [10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
tMotors testMotor = motorA;


task main()
{

	for (int count = 0; count < testCases; count++)
	{
		time1[T1] = 0;
		nMotorEncoder[testMotor] = 0;
		motor[testMotor] = testCases [count];

		while (time1[T1] < 1000)
		{}
		displayString(count, "%f mm", nMotorEncoder[testMotor]/MM_TO_ENC);
		motor[testMotor] = -25;
		while (nMotorEncoder[testMotor] > 0)
		{}
		motor[testMotor] = 0;

	}
	wait1Msec(600000);


}
