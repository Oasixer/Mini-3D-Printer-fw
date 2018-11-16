#include "global.c"
#include "move.c"

#ifndef PRINT_C
#define PRINT_C

void printSquare (float leftx, float boty){
	extrude(true);
	wait1Msec(300);

	moveXY(leftx,boty);
	moveXY(leftx+15,boty);
	moveXY(leftx+15,boty+15);
	moveXY(leftx,boty+15);

	int xTarget = 0, yTarget = 1;
	for (int pattern = 0; pattern < 7; pattern++)
	{
		for (int count = 0; count < 4; count++)
		{
			if (count == 0 || count == 3)
				xTarget = 1;
			else
				// Make pbv variable to make size of square adjustable
				xTarget = 14;

				if (count == 2)
					yTarget++;

			moveXY(leftx+xTarget, boty+yTarget);
		}
	}

	//moveXY(leftx,boty);
	//moveXY(leftx+14,boty+0);
	//moveXY(leftx+14,boty+14);
	//moveXY(leftx,boty+14);
	//moveXY(leftx,boty+1);
	//moveXY(leftx+13,boty+1);
	//moveXY(leftx+13,boty+13);
	//moveXY(leftx+1,boty+13);
	//moveXY(leftx+1,boty+2);
	//moveXY(leftx+12,boty+2);
	//moveXY(leftx+12,boty+3);
	//moveXY(leftx+2,boty+3);
	//moveXY(leftx+2,boty+4);
	//moveXY(leftx+12,boty+4);
	//moveXY(leftx+12,boty+5);
	//moveXY(leftx+2,boty+5);
	//moveXY(leftx+2,boty+6);
	//moveXY(leftx+12,boty+6);
	//moveXY(leftx+12,boty+7);
	//moveXY(leftx+2,boty+7);
	//moveXY(leftx+2,boty+8);
	//moveXY(leftx+12,boty+8);
	//moveXY(leftx+12,boty+9);
	//moveXY(leftx+2,boty+9);
	//moveXY(leftx+2,boty+10);
	//moveXY(leftx+12,boty+10);
	//moveXY(leftx+12,boty+11);
	//moveXY(leftx+2,boty+11);
	//moveXY(leftx+2,boty+12);
	//moveXY(leftx+12,boty+12);
	extrude(false);
}

void runPrint (){
	for (int layer = 1; layer < MAXLAYER; layer++){
		for (float x = 0; x < 5; x++){
			for (float y = 0; y < 5; y++){
				if (cubes[x][y] >= layer)
					printSquare(x, y);
			}
		}
		moveZ(layer*LAYERHEIGHT);
	}
}

#endif