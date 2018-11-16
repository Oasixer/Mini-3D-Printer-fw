#include "global.c"
#include "move.c"
#include "buttons.c"

void configureI2C (tSensors port){ // make sure to call function to set up servo
	SensorType[port] = sensorI2CCustom9V;
}

void zeroAxis(tMotor motorAxis, int powerAxis, tSensorw touchAxis)
{
	// zero x-axis
	motor[motorAxis] = powerAxis;
	while(SensorValue[touchAxis] == 0) {}
	motor[motorAxis] = 0;
	nMotorEncoder[motorAxis] = 0;
}

void zero(tSensors touchY, tSensors touchZ, int velocity)
{	
	powerX = -velocity;
	powerY = -velocity;
	powerZ = max(-2*velocity, -100);
	
	// zero y,z-axis
	zeroAxis(motorY, -velocity, touchY);
	zeroAxis(motorZ, -max(-2*velocity, -100), touchZ);
	
	// zero x-axis
	
	moveXY(1, 1);
	moveZ(1);
	
	// zero at half speed
	// zero y,z-axis
	zeroAxis(motorY, -velocity/2, touchY);
	zeroAxis(motorZ, -max(-velocity, -100), touchZ);
	
	//zero x-axis
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
	for (int x=0;x<6;x++){
		for(int y=0;y<6;y++){
			step=1.1;//DEBUG
			moveXY(x*15+7.5,y*15+7.5);
			step=1.9;//DEBUG
			cubes[x][y]=scanColour();
		}
	}
}
