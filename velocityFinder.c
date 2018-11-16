// velocity finder by Zachariah Mears
// used to calibrate motorPower function
//#include<global.c>

int testCases [10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
const float MM_TO_ENC = 15;
tMotor testMotor = motorD;
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
