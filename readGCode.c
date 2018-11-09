// RobotC functions
#include "PCFileIO.c"
void readFile(TFileHandle & fin, string filename){
	openReadPC(fin, filename);
	
	float xLast = 0, yLast = 0;
	if (readFloatPC(fin, xLast) && readFloatPC(fin, yLast))
	{
		// move to first position
		moveXYMM(xLast, yLast, false);
		// turn on extruder
		
		float xNext = 0, yNext = 0;
		while(readFloatPC(fin, xNext) && readFloatPC(fin, yNext))
		{
			// move to next position
			moveXYMM(xNext-xLast, yNext-yLast, true);
		}
		
		// turn off extruder
	}	
	closeFilePC(fin);
	

// GCode text

