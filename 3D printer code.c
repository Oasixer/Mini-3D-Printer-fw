// by Zachariah, Kaelan, Lyndon, Daddy Parth
#include<global.c>
#include<move.c>
#include<start.c>
#include<print.c>

const tMotor motorY = motorA, motorX = motorD;
const tMotor motorZ = motorB, motorE = motorC;
const float ENCTOMM=(float)24/360;

//GLOBAL VARIABLES ABOVE HERE



//FUNCTIONS BELOW HERE




//cubes[][][] stores all the cubes in a cartesian plane.
//dimension 1=x axis, dimension 2=y axis, dimension 3=z axis
//value = 1 if it needs to be printed, 0 if not. (possibly add like 2 for things that have been printed already??)

void test (){ //makes a 5cm horizontal line and a 5cm line at a 45 degree angle
	nMotorEncoder[motorX]=0;
	nMotorEncoder[motorY]=0;
	wait1Msec(50);
	step=0;
	moveXY(0,5);
	step=1;
	moveXY(5,5);
	step=2;
}
*/

//TASK MAIN

task main ()
{
	/*
	maxLayer=0;
	int cubes[5][5]=scanPaper();
	bool printing=false; //temp, use a button press or something
	while (printing){
		for (int lay=0; lay<maxLayer+1; lay++){ //loop through layers
			for (int x=0; x<5; x++){ //loop through columns (x)
				for (int y=0; y<5; y++){ //loop h
					if (cubes[x][y]){
						printSquare((float)x*15,(float)y*15);
					}
				}
			}
		}
	}
	*/
	//test();
printSquare(0,0);
}
