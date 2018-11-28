/*
Group 414
3D Printer
Tests to find the velocity at given motor powers
*/

int testCases [10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
const float MM_TO_ENC = 15;
tMotor testMotor = motorD;
task main()
{

	for (int count = 0; count < testCases; count++) //loop through the test cases
	{
		time1[T1] = 0;
		nMotorEncoder[testMotor] = 0;
		motor[testMotor] = testCases [count];

		while (time1[T1] < 1000)
		{}
		displayString(count, "%f mm", nMotorEncoder[testMotor]/MM_TO_ENC); //display the velocity (mm traveled in 1s)
		motor[testMotor] = -25;
		while (nMotorEncoder[testMotor] > 0) //return to original position
		{}
		motor[testMotor] = 0;

	}
	wait1Msec(600000); //wait arbitrarily long to look at the output velocity


}
