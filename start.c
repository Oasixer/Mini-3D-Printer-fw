#include "global.c"
#include "move.c"
#include "buttons.c"

void configureI2C (tSensors port){ // make sure to call function to set up servo
	SensorType[port] = sensorI2CCustom9V;
}

void zeroAxis(tMotor motorAxis, int powerAxis, tSensor touchAxis)
{
	// zero x-axis
	motor[motorAxis] = powerAxis;
	while(SensorValue[touchAxis] == 0) {}
	motor[motorAxis] = 0;
	nMotorEncoder[motorAxis] = 0;
}

void zero(tSensor touchX, tSensor touchY, tSensor touchZ, int velocity){
	
	powerX = -veloctiy;
	powerY = -velocity;
	powerZ = max(-2*velocity, -100);
	
	// zero x-axis
	zeroAxis(motorX, -velocity, touchX);
	zeroAxis(motorY, -velocity, touchY);
	zeroAxis(motorZ, -max(-2*velocity, -100), touchZ);
	
	moveXY(1, 1);
	moveZ(1);
	
	zeroAxis(motorX, -velocity/2, touchX);
	zeroAxis(motorY, -velocity/2, touchY);
	zeroAxis(motorZ, -max(-velocity, -100), touchZ);
	
	// motor[motorX] = powerX;
	// while(SensorValue[touchX] == 0) {}
	// motor[motorX] = 0;
	// nMotorEncoder[motorX] = 0;
	
	// zero y-axis
	
	// motor[motorY] = powerY;
	// while(SensorValue[touchY] == 0) {}
	// motor[motorY] = 0;
	// nMotorEncoder[motorY] = 0;
	
	// zero z-axis
	// motor[motorZ] = powerZ;
	// while(SensorValue[touchZ] == 0) {}
	// motor[motorZ] = 0;
	// nMotorEncoder[motorZ] = 0;
	
	// moX=-20;
	// motor[motorX]=moX;
	// waitForButtonPress();
	// moX=0;
	// motor[motorX]=moX;

	// // zero Y
	// SensorType[S2]=sensorEV3_Touch;
	// SensorMode[S2]=modeEV3Touch_Touch;
	// moY=-50;
	// // wait for sensor
	// moY=0;//UNFINISHED
	
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
			moveXY(x*15+7,y*15+7.5);
			step=1.9;//DEBUG
			cubes[x][y]=scanColour();
		}
	}
}