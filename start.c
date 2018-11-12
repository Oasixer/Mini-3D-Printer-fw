#include<global.c>
#include<move.c>
#include<buttons.c>

void zero(){
	//zero X
	moX=-20;
	motor[motorX]=moX;
	waitForButtonPress();
	moX=0;
	motor[motorX]=moX;

	//zero Y
	SensorType[S2]=sensorEV3_Touch;
	SensorMode[S2]=modeEV3Touch_Touch;
	moY=-50;
	//wait for sensor
	moY=0;//UNFINISHED
	
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
			moveXY(x*15-7,y*15-7);
			step=1.9;//DEBUG
			cubes[x][y]=scanColour();
		}
	}
}
