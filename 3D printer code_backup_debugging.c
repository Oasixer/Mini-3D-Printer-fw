// by Zachariah, Kaelan, Lyndon, Daddy Parth
const int velocity = 25; //mm/s 200/8
const float encoderCountPermm = 180/PI*4;
const float TOLERANCE = 1;
const tMotor motorY = motorA, motorX = motorD;
const tMotor motorZ = motorB, motorE = motorC;
float deX, deY, moX,moY, yTar, xTar, xIni, yIni, xCu, yCu, xEn, yEn;
const float ENCTOMM=(float)24/360;
const float MMTOENC=15;
int maxLayer;
int step=0;
//GLOBAL VARIABLES ABOVE HERE

//PROTOTYPES
void moveXYMM (float xTarget, float yTarget, bool rel);
int scanPaper();
int scanColour();
void moveServo(bool input);
void test();
float motorPower(float velocity);

//STRUCTS
struct Vector {
	float x;
	float y;
	float magnitude;
};

float getMagnitude (struct Vector v)
{
	return sqrt(x*x + y*y);
}




//FUNCTIONS BELOW HERE

float motorPower (float velocity)
{
	const float slope = 1, offset = 0, exponent = 1;
	if (velocity < 0)
	{
	return -slope*pow(abs(velocity), exponent) + offset;
	}
	else
	{
		return slope*pow(abs(velocity), exponent) + offset;
	}
}

//kaelans version of moveXY
//changes: 1) take xTarget and yTarget in mm
//2) do all the calculations relative to the starting x and y
//so that we dont lose track of the total movement of the extruder

//this constant needs to be filled in - its the ratio of encoder counts to millimeters

void moveXYMM (float xTarget, float yTarget)
{
	float xCur=nMotorEncoder[motorX]*ENCTOMM;
	float yCur=nMotorEncoder[motorY]*ENCTOMM;
	xTar=xTarget;
	yTar=yTarget;
	float deltaX = xTarget-xCur;
	deX=deltaX;
	float deltaY = yTarget-yCur; //AHHHH remember to fix indeterminate case below when deltaX or deltaY==0
	deY=deltaY;
	//displayString(0,"dx=%f")
	moX=motor[motorX] = motorPower((velocity*(deltaX/sqrt(deltaX*deltaX+deltaY*deltaY))));
	moY=motor[motorY] = motorPower((velocity*(deltaY/sqrt(deltaX*deltaX+deltaY*deltaY))));
	motor[motorY]=moY;


	while (abs(xTarget - xCur)>TOLERANCE || abs(yTarget - yCur)>TOLERANCE){
		xEn=nMotorEncoder[motorX];
		yEn= nMotorEncoder[motorY];
		xCur=nMotorEncoder[motorX]*ENCTOMM-xInit;
		yCur=nMotorEncoder[motorY]*ENCTOMM-yInit;
		xCu=xCur;
		yCu=yCur;
		if (abs(xTarget - xCur)<TOLERANCE)
		{
			motor[motorX] = 0;
		}
		if (abs(yTarget - yCur)<TOLERANCE)
		{
			motor[motorY] = 0;
		}
	}
	motor[motorX]=0;
	motor[motorY]=0;
}

int scanColour(){
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


//cubes[][][] stores all the cubes in a cartesian plane.
//dimension 1=x axis, dimension 2=y axis, dimension 3=z axis
//value = 1 if it needs to be printed, 0 if not. (possibly add like 2 for things that have been printed already??)
int scanPaper(){
	int cubes[5][5];
	for (int x=0;x<6;x++){
		for(int y=0;y<6;y++){
			moveXYMM(x*15,y*15,false);
				int height=scanPaper();
			if (height>maxLayer)
				maxLayer=height;
			cubes[x][y]=height;
		}
	}
	return cubes;
}


//done
void printSquare (float leftx, float boty){
	moveXYMM(leftx,boty,false);
	moveXYMM(leftx+14,boty+0,false);
	moveXYMM(leftx+14,boty+14,false);
	moveXYMM(leftx,boty+14,false);
	moveXYMM(leftx,boty+1,false);
	moveXYMM(leftx+13,boty+1,false);
	moveXYMM(leftx+13,boty+13,false);
	moveXYMM(leftx+1,boty+13,false);
	moveXYMM(leftx+1,boty+2,false);
	moveXYMM(leftx+12,boty+2,false);
	moveXYMM(leftx+12,boty+3,false);
	moveXYMM(leftx+2,boty+3,false);
	moveXYMM(leftx+2,boty+4,false);
	moveXYMM(leftx+12,boty+4,false);
	moveXYMM(leftx+12,boty+5,false);
	moveXYMM(leftx+2,boty+5,false);
	moveXYMM(leftx+2,boty+6,false);
	moveXYMM(leftx+12,boty+6,false);
	moveXYMM(leftx+12,boty+7,false);
	moveXYMM(leftx+2,boty+7,false);
	moveXYMM(leftx+2,boty+8,false);
	moveXYMM(leftx+12,boty+8,false);
	moveXYMM(leftx+12,boty+9,false);
	moveXYMM(leftx+2,boty+9,false);
	moveXYMM(leftx+2,boty+10,false);
	moveXYMM(leftx+12,boty+10,false);
	moveXYMM(leftx+12,boty+11,false);
	moveXYMM(leftx+2,boty+11,false);
	moveXYMM(leftx+2,boty+12,false);
	moveXYMM(leftx+12,boty+12,false);
}

//NOT DONE NOT DONE NOT DONE
void zero(){
	//add later
}

/*
void moveServo (bool input){
	if (input){
		setServoPosition(S4, 1, 25);// extrude on
	}
	else {
		setServoPosition(S4, 1, 0);//extrude off
	}
}
*/

void test (){ //makes a 5cm horizontal line and a 5cm line at a 45 degree angle
	nMotorEncoder[motorX]=0;
	nMotorEncoder[motorY]=0;
	wait1Msec(50);
	step=0;
	moveXYMM(0,5,true);
	step=1;
	moveXYMM(5,5,true);
	step=2;
}


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
	maxLayer=2;
	test();

}
