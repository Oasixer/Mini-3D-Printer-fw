#include "global.c"
#include "move.c"
#include "buttons.c"

#ifndef START_C
#define START_C

float max(float number1, float number2)
{
	if (number1 > number2)
		return number1;
	return number2;
}

void configureI2C (tSensors port){ // make sure to call function to set up servo
	SensorType[port] = sensorI2CCustom9V;
}

void zero(tSensors touchY, tSensors touchZ, int velocity)
{
	float powerX = -velocity;
	float powerY = -velocity;
	float powerZ = max(-2*velocity, -100);

	// zero x-axis
	motor[motorX] = 7;
	motor[motorZ1] = 100;
	motor[motorZ2] = 100;
	wait1Msec(1000);
	motor[motorZ1] = motor[motorZ2] = 0;
	wait1Msec(25000);
	motor[motorX] = 0;

	// zero y-axis
	motor[motorY] = powerY;
	while(SensorValue[touchY] == 0) {}
	motor[motorY] = 0;
	nMotorEncoder[motorY] = 0;

	// zero z-axis
	motor[motorZ1] = motor[motorZ2] = powerZ;
	while(SensorValue[touchZ] == 0) {}
	motor[motorZ1] = motor[motorZ2] = 0;
	nMotorEncoder[motorZ1] = 0;
	nMotorEncoder[motorZ2] = 0;

	moveXY(0, 20);
	moveZ(20);

	// zero y-axis at quarter speed
	motor[motorY] = powerY / 4;
	while(SensorValue[touchY] == 0) {}
	motor[motorY] = 0;
	nMotorEncoder[motorY] = 0;

	// zero z-axis at quarter speed
	motor[motorZ1] = motor[motorZ2] = powerZ / 2;
	while(SensorValue[touchZ] == 0) {}
	motor[motorZ1] = motor[motorZ2] = 0;
	nMotorEncoder[motorZ1] = 0;
	nMotorEncoder[motorZ2] = 0;

}

int scanColour()
{
	SensorType[S1]=sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S1]=modeEV3Color_Color;
	wait1Msec(50);

	int values[3]; //store 3 colour values
	do{ //loop until all 3 colour values are the same (aka make sure you dont read the wrong colour)
		values[0]=(int)SensorValue[S1];
		wait1Msec(50);
		values[1]=(int)SensorValue[S1];
		wait1Msec(50);
		values[2]=(int)SensorValue[S1];
		wait1Msec(50);
	} while (!(values[0]==values[1]&&values[0]==values[2]));
		return values[2];
}

void scanPaper(){
	for (int x = 0; x < 6; x++){
		for(int y = 0; y < 6; y++){
			step=1.1;//DEBUG
			moveXY(x*15+7.5,y*15+7.5);
			step=1.9;//DEBUG
			cubes[x][y]=scanColour();
		}
	}
}

#endif
