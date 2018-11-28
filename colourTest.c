/*
Group 414
3D Printer

Testing Procedure for colour values
Procedure: scan 5x5 grid of coloured squares, assign the integer corresponding to the scanned colour to the testing data array.
*/
#include "move.c"
int values[3]; 		//store 3 colour values
int colourTest[5];//test one row of the grid
int scanColour(){
	SensorType[S1]=sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S1]=modeEV3Color_Color;
	wait1Msec(50);


	do{ //loop until all 3 colour values are the same (make sure you dont read the wrong colour)
		values[0]=(int)SensorValue[S1];
		wait1Msec(50);
		values[1]=(int)SensorValue[S1];
		wait1Msec(50);
		values[2]=(int)SensorValue[S1];
		wait1Msec(50);
	} while (!(values[0]==values[1] && values[0]==values[2]));
		return values[2];
}

task main()
{
	for (int i = 0; i < 5; i++) //loop runs once for each square in a row 
	{
		moveXY(i * 15,0); //move to the next square's location (robot will be manually zeroed to the center of the first square)
		colourTest[i] = scanColour();
	}
}
