
/*
Testing Procedure for colour values
testing procedure for testing involves the scanning of the colour on 
a grid involving 7 colours
*/
int values[3]; 		//store 3 colour values
int colourTest[7];
int scanColour()
{
	SensorType[S1]=sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S1]=modeEV3Color_Color;
	wait1Msec(50);


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

task main()
{
	for (int i = 0; i < 7; ++i)
	{
		
	}
}


