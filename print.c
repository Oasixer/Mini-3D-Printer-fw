#include "global.c"
#include "move.c"

#ifndef PRINT_C
#define PRINT_C

void printSquare (float leftx, float boty){ //prints one square at the given coordinates
	moveXY(leftx,boty); //move to starting coordinates
	extrude(true); //start extruding
  wait1Msec(900); //wait for the filament to start coming out
	moveXY(leftx+14,boty); //start tracing out the square using the move commands
	moveXY(leftx+14,boty+13);
	moveXY(leftx,boty+13);
	moveXY(leftx,boty+0.35);
	moveXY(leftx+13,boty+0.35);
	moveXY(leftx+13,boty+12);
	moveXY(leftx+1,boty+12);
	moveXY(leftx+1,boty+1.15);
	moveXY(leftx+12,boty+1.15);
	moveXY(leftx+12,boty+2);
	moveXY(leftx+2,boty+2);
	moveXY(leftx+2,boty+3);
	moveXY(leftx+12,boty+3);
	moveXY(leftx+12,boty+4);
	moveXY(leftx+2,boty+4);
	moveXY(leftx+2,boty+5);
	moveXY(leftx+12,boty+5);
	moveXY(leftx+12,boty+6);
	moveXY(leftx+2,boty+6);
	moveXY(leftx+2,boty+7);
	moveXY(leftx+12,boty+7);
	moveXY(leftx+12,boty+8);
	moveXY(leftx+2,boty+8);
	moveXY(leftx+2,boty+9);
	moveXY(leftx+12,boty+9);
	moveXY(leftx+12,boty+10);
	moveXY(leftx+2,boty+10);
	moveXY(leftx+2,boty+11);
	extrude(false); //stop extruding. this is called before the last movement to account for the lag of the extruder 
	moveXY(leftx+12,boty+11);
}

void runPrint (){ //prints the entire array of cubes
	for (int layer = 1; layer < MAXLAYER; layer++){ //loop through every layer in the print
		moveZ(layer*LAYERHEIGHT); //move to the height of the current layer
		for (int x = 0; x < 5; x++){ //loop through the columns
			for (int y = 0; y < 5; y++){ //loop through the rows
				if ((float)(cubes[x][y])*(CUBEHEIGHT/LAYERHEIGHT) >= layer) //check if the data includes a square at the current x,y and layer 
					printSquare((float)x*15.0, (float)y*15.0); //print a square
			}
		}
	}
}

#endif
