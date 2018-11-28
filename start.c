/*
Group 414
3D Printer
Startup functions
*/

#include "global.c"
#include "move.c"
#include "buttons.c"
#include "misc.c"

#ifndef START_C
#define START_C

void configureI2C (tSensors port){ //set up servo
	SensorType[port] = sensorI2CCustom9V;
}

void zero()
{
	float powerX = -50;
	float powerY = -50;
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
	motor[motorZ1] = 100; //power Z axis for 2 seconds to lift clear of any obstacles before zeroing
	motor[motorZ2] = 95; //power difference between Z1 and Z2 accounts for friction difference
	wait1Msec(2000);
	motor[motorZ1] = motor[motorZ2] = 0;
	time1[T1]=0;
  //this loops until the x axis is at zero, detected by the motor getting stuck (we poll the encoder)
	while (deltaEnc != 0){
		encVal1 = nMotorEncoder[motorX];
		wait1Msec(60);
		encVal2 = nMotorEncoder[motorX];
		deltaEnc = encVal2 - encVal1;
	}
	motor[motorX] = 0;
	nMotorEncoder(motorX)=0;

	// zero y-axis
	motor[motorY] = powerY;
	while(SensorValue[TOUCH_Y] == 0) {} //wait until the touch sensor is hit
	motor[motorY] = 0;
	nMotorEncoder[motorY] = 0;

	// zero z-axis
	motor[motorZ1] = powerZ;
	motor[motorZ2] = -95;
	while(SensorValue[TOUCH_Z] == 0) {wait1Msec(15);} //wait until the touch sensor is hit
	motor[motorZ1] = motor[motorZ2] = 0;
	nMotorEncoder[motorZ1] = 0;
	nMotorEncoder[motorZ2] = 0;

	moveZ(8);
	moveXY(5, 20);

	// rezero y-axis at quarter speed for more accurate distance
	motor[motorY] = powerY / 4.0;
	while(SensorValue[TOUCH_Y] == 0) {}
	motor[motorY] = 0;
	nMotorEncoder[motorY] = 0;

	// rezero z-axis at half speed for more accurate distance
	motor[motorZ1] = powerZ / 2;
	motor[motorZ2] = -47;
	while(SensorValue[TOUCH_Z] == 0) {}
	motor[motorZ1] = motor[motorZ2] = 0;
	wait1Msec(50);
	nMotorEncoder[motorZ1] = 0;
	nMotorEncoder[motorZ2] = 0;


	wait1Msec(50);
	moveZ(7); //move to the bottom corner of the printbed (the new zero)
	moveXY(16, 51);
	wait1Msec(50);
	moveZ(3.7);
  
  //this allows the user to make adjustments to the x,y,z position in case the robot zeroes incorrectly
  //it will time out after 5 seconds; the user has 5 seconds to start using the buttons to make commands
  //otherwise the program will continue without adjustments
  //up, down, left, and right buttons are used for movement. the enter button is pressed to switch modes
  //to finish adjustments, hold down the enter button for 600ms.

	bool xyMode=true; //stores the adjustment mode. true is x,y adjustments. false is z adjustments
	bool quit=false; //used to exit the loop early if the user does not want to adjust anything
	time1[T1]=0;
	while(!getButtonPress(buttonAny)&&time1[T1]<5800){
		if (time1[T1]>5600)
			quit=true;
	}
	while(!quit){
		if (xyMode){
      //XY MODE: up, down, left, and right buttons will move the x and y axis
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
      //Z MODE: up, down, buttons will move the Z2 motor. left, right buttons move the Z1 motor
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
    //mode switching / exit
		if (getButtonPress(buttonEnter)){
			xyMode=!xyMode; //switch mode
			motor[motorX]=0; //stop all motors
			motor[motorY]=0;
			motor[motorZ1]=0;
			motor[motorZ2]=0;
			time1[T1]=0;
			while(getButtonPress(buttonEnter)){ //check if the user holds the button long enough to exit loop
				if (time1[T1]>600)
					quit=true;
		  }
		}
	}
 //stop all motors, zero all encoders. the robot is assumed to be correctly zeroed now since the user has made any adjustments neccesary
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
	do{ //loop until all 3 colour values are the same (make sure you dont read the wrong colour)
		values[0]=(int)SensorValue[S1];
		wait1Msec(50);
		values[1]=(int)SensorValue[S1];
		wait1Msec(50);
		values[2]=(int)SensorValue[S1];
		wait1Msec(50);
	} while (!(values[0]==values[1]&&values[0]==values[2]));
	int colorInt=values[2];
	wait1Msec(50);
  //return cube heights based on colours
  //white = 0 cubes
  //yellow = 1 cube
  //red = 2 cubes
  //brown = 3 cubes
  //green = 4 cubes
  //black = 5 cubes
	if (colorInt==(int)colorWhite || colorInt==(int)colorBlue)//white sometimes is detected as blue, so blue scans to white to fix that
		return 0;
	else if (colorInt==(int)colorYellow)
		return 1;
	else if (colorInt==(int)colorRed)
		return 2;
  else if (colorInt==(int)colorBrown)
    return 3;
	else if (colorInt==(int)colorGreen)
		return 4;
	else if (colorInt==(int)colorBlack)
		return 5;
	return 0;
}

void scanPaper(){
	SensorType[S1]=sensorEV3_Color; //setup sensor
	wait1Msec(70);
	SensorMode[S1]=modeEV3Color_Color;
	wait1Msec(70);
	moveZ(3); //move up the Z axis to make sure that the extruder is clear of any obstructions
	for (int xLoc = 0; xLoc < 5; xLoc++){ //loop through columns
		for(int yLoc = 0; yLoc < 5; yLoc++){ //loop through rows
			moveXY((float)xLoc*15.0-4.5,(float)yLoc*15.0+37.5); //scan the center of the given square
			cubes[xLoc][yLoc]=scanColour(); //fill in the cube data array based on int returned by scancolour
		}
	}

}
#endif
