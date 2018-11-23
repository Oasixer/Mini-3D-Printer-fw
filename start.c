#include "global.c"
#include "move.c"
#include "buttons.c"
#include "math.c"

#ifndef START_C
#define START_C

void configureI2C (tSensors port){ // make sure to call function to set up servo
	SensorType[port] = sensorI2CCustom9V;
}

void zero()
{
	float powerX = -50;
	float powerY = -50;
	float powerZ = -100;
	float deltaEnc = 1;
	float encVal1 = 0;
	float encVal2 = 0;

	//hit the pen to make sure it warms up
	extrude(false);
	wait1Msec(100);
	extrude(true);
	wait1Msec(800);
	extrude(false);

	// zero x-axis
	motor[motorX] = 12;
	motor[motorZ1] = 100;
	motor[motorZ2] = 100;
	wait1Msec(2000);
	motor[motorZ1] = motor[motorZ2] = 0;
	time1[T1]=0;
	while (time1[T1]<25000 && deltaEnc != 0 && !getButtonPress(buttonAny)){
		encVal1 = nMotorEncoder[motorX];
		wait1Msec(60);
		encVal2 = nMotorEncoder[motorX];
		deltaEnc = encVal2 - encVal1;
	}
	motor[motorX] = 0;
	nMotorEncoder(motorX)=0;

	// zero y-axis
	motor[motorY] = powerY;
	while(SensorValue[TOUCH_Y] == 0) {}
	motor[motorY] = 0;
	nMotorEncoder[motorY] = 0;

	// zero z-axis
	motor[motorZ1] = motor[motorZ2] = powerZ;
	while(SensorValue[TOUCH_Z] == 0) {wait1Msec(15);}
	motor[motorZ1] = motor[motorZ2] = 0;
	nMotorEncoder[motorZ1] = 0;
	nMotorEncoder[motorZ2] = 0;

	moveZ(8);
	moveXY(5, 20);

	// zero y-axis at quarter speed
	motor[motorY] = powerY / 4.0;
	while(SensorValue[TOUCH_Y] == 0) {}
	motor[motorY] = 0;
	nMotorEncoder[motorY] = 0;

	// zero z-axis at half
	motor[motorZ1] = motor[motorZ2] = powerZ / 2;
	while(SensorValue[TOUCH_Z] == 0) {}
	motor[motorZ1] = motor[motorZ2] = 0;
	wait1Msec(50);
	nMotorEncoder[motorZ1] = 0;
	nMotorEncoder[motorZ2] = 0;


	wait1Msec(50);
	moveZ(5);
	wait1Msec(50);
	moveXY(14, 50);
	//moveXY(31,28);
	wait1Msec(50);
	moveZ(3.25);
	bool xyMode=true;
	bool quit=false;
	time1[T1]=0;
	while(!getButtonPress(buttonAny)&&time1[T1]<5800){
		if (time1[T1]>5600)
			quit=true;
	}
	while(!quit){
		if (xyMode){
			if (getButtonPress(buttonLeft))
				motor[motorX]=15;
			else if (getButtonPress(buttonRight))
				motor[motorX]=-15;
			else
				motor[motorX]=0;
			if (getButtonPress(buttonUp))
				motor[motorY]=-15;
			else if (getButtonPress(buttonDown))
				motor[motorY]=15;
			else
				motor[motorY]=0;
		}
		else{
			if (getButtonPress(buttonLeft))
				motor[motorZ1]=50;
			else if (getButtonPress(buttonRight))
				motor[motorZ1]=-50;
			else
				motor[motorZ1]=0;
			if (getButtonPress(buttonUp))
				motor[motorZ2]=50;
			else if (getButtonPress(buttonDown))
				motor[motorZ2]=-50;
			else
				motor[motorZ2]=0;
		}
		if (getButtonPress(buttonEnter)){
			xyMode=!xyMode;
			motor[motorX]=0;
			motor[motorY]=0;
			motor[motorZ1]=0;
			motor[motorZ2]=0;
			time1[T1]=0;
			while(getButtonPress(buttonEnter)){
				if (time1[T1]>600)
					quit=true;
		  }
		}
	}
	motor[motorX]=0;
	motor[motorY]=0;
	motor[motorZ1]=0;
	motor[motorZ2]=0;
	nMotorEncoder[motorX] = 0;
	nMotorEncoder[motorY] = 0;
	nMotorEncoder[motorZ1] = 0;
	nMotorEncoder[motorZ2] = 0;


}

int scanColour()
{

	int values[3]; //store 3 colour values
	do{ //loop until all 3 colour values are the same (aka make sure you dont read the wrong colour)
		values[0]=(int)SensorValue[S1];
		wait1Msec(50);
		values[1]=(int)SensorValue[S1];
		wait1Msec(50);
		values[2]=(int)SensorValue[S1];
		wait1Msec(50);
	} while (!(values[0]==values[1]&&values[0]==values[2]));
	int colorInt=values[2];
	wait1Msec(50);
	if (colorInt==(int)colorWhite || colorInt==(int)colorBlue)
		return 0;
	else if (colorInt==(int)colorYellow)
		return 1;
	else if (colorInt==(int)colorRed||colorInt==(int)colorBrown)
		return 2;
	else if (colorInt==(int)colorGreen)
		return 3;
	else if (colorInt==(int)colorBlack)
		return 4;
	return 0;
}

void scanPaper(){
	step=0;
	SensorType[S1]=sensorEV3_Color;
	wait1Msec(70);
	SensorMode[S1]=modeEV3Color_Color;
	wait1Msec(70);
	moveZ(3);
	for (int xLoc = 0; xLoc < 5; xLoc++){
		for(int yLoc = 0; yLoc < 5; yLoc++){
			moveXY((float)xLoc*15.0-4.5,(float)yLoc*15.0+37.5);
			cubes[xLoc][yLoc]=scanColour();
		}
	}

}
#endif
