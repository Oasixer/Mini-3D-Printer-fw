#include<constants.c>
#include<move.c>

void printSquare (float leftx, float boty){
	extrude(true);
	wait1MSec(300);
	moveXY(leftx,boty);
	moveXY(leftx+14,boty+0);
	moveXY(leftx+14,boty+14);
	moveXY(leftx,boty+14);
	moveXY(leftx,boty+1);
	moveXY(leftx+13,boty+1);
	moveXY(leftx+13,boty+13);
	moveXY(leftx+1,boty+13);
	moveXY(leftx+1,boty+2);
	moveXY(leftx+12,boty+2);
	moveXY(leftx+12,boty+3);
	moveXY(leftx+2,boty+3);
	moveXY(leftx+2,boty+4);
	moveXY(leftx+12,boty+4);
	moveXY(leftx+12,boty+5);
	moveXY(leftx+2,boty+5);
	moveXY(leftx+2,boty+6);
	moveXY(leftx+12,boty+6);
	moveXY(leftx+12,boty+7);
	moveXY(leftx+2,boty+7);
	moveXY(leftx+2,boty+8);
	moveXY(leftx+12,boty+8);
	moveXY(leftx+12,boty+9);
	moveXY(leftx+2,boty+9);
	moveXY(leftx+2,boty+10);
	moveXY(leftx+12,boty+10);
	moveXY(leftx+12,boty+11);
	moveXY(leftx+2,boty+11);
	moveXY(leftx+2,boty+12);
	moveXY(leftx+12,boty+12);
	extrude(false);
}

void runPrint (int cubes[5][5]){
	for (int layer=1;layer<MAXLAYER;layer++){
		for (float x=0;x<5;x++){
			for (float y=0;y<5;y++){
				if (cubes[x][y]<=layer)
					printSquare(x,y);
			}
		}
		moveZ(layer*LAYERHEIGHT);
	}

}
