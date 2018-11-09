// by Zachariah Mears
const int velocity = 25; //mm/s 200/8
const float encoderCountPermm = 180/PI*4;
const float TOLERANCE = 2;
int motorX = motorA, motorY = motorB, motorZ = motorC, motorE = motorD;


float motorPower (float velocity); //func prototype
void moveXY (float xTarget, float yTarget)
{
	float deltaX = xTarget - nMotorEncoder[motorX];
	float deltaY = yTarget - nMotorEncoder[motorY];

	motor[motorX] = motorPower(velocity*encoderCountPermm*deltaX/sqrt(pow(deltaX,2) + pow(deltaY,2)));
	motor[motorY] = motorPower(velocity*encoderCountPermm*deltaY/sqrt(pow(deltaX,2) + pow(deltaY,2)));

	while (abs(xTarget - nMotorEncoder[motorX])>TOLERANCE || abs(yTarget - nMotorEncoder[motorY])>TOLERANCE)
	{
		if (abs(xTarget - nMotorEncoder[motorX])<TOLERANCE)
		{
			motor[motorX] = 0;
		}
		if (abs(yTarget - nMotorEncoder[motorY])<TOLERANCE)
		{
			motor[motorY] = 0;
		}
	}
}

//kaelans version of moveXY
//changes: 1) take xTarget and yTarget in mm
//2) do all the calculations relative to the starting x and y 
//so that we dont lose track of the total movement of the extruder

//this constant needs to be filled in - its the ratio of encoder counts to millimeters
const float ENCTOMM=24/360;
const float MMTOENC=15;
int maxLayer=0;

void moveXYMM (float xTarget, float yTarget, bool rel)
{	
	float xCur=nMotorEncoder[motorX]*ENCTOMM;
	float yCur=nMotorEncoder[motorY]*ENCTOMM;
	float xInit=xCur;
	float yInit=yCur;
	if (!rel){
		xInit=0;
		yInit=0;
	}
	xCur-=xInit;
	yCur-=yInit;

	float deltaX = xTarget-xCur;
	float deltaY = yTarget-yCur; //fix indeterminate below
	motor[motorX] = motorPower((abs(deltaX)/deltaX)(velocity*(deltaX/sqrt(deltaX*deltaX+deltaY*deltaY))));
	motor[motorY] = motorPower((abs(deltaY)/deltaY)(velocity*(deltaY/sqrt(deltaX*deltaX+deltaY*deltaY))));
	while (abs(xTarget - xCur)>TOLERANCE || abs(yTarget - yCur)>TOLERANCE){
		xCur=nMotorEncoder[motorX]*ENCTOMM-xInit;
		yCur=nMotorEncoder[motorY]*ENCTOMM-yInit;
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

task main ()
{
	int cubes[10][10][300]=scanPaper();
	boolean printing=false; //temp, use a button press or something
	while (printing){
		for (int lay=0; lay<maxLayer+1; lay++){ //loop through layers
			for (int x=0; x<15; x++){ //loop through columns (x)
				for (int y=0; y<15; y++){ //loop h
					if (cubes[layer][x][y]){
						printSquare((float)x*15,(float)y*15);
					}
				}
			}
		}
	}
}

//cubes[][][] stores all the cubes in a cartesian plane. 
//dimension 1=x axis, dimension 2=y axis, dimension 3=z axis
//value = 1 if it needs to be printed, 0 if not. (possibly add like 2 for things that have been printed already??)
int scanPaper(){
	int cubes[10][10][300]={0};
	//add later
	//remember to assign maxLayer
	maxLayer=0; //temp
	for (int i=0;i<31;i++){
		cubes[0][0][i]=1; //TEST CASE MATRIX: JUST 2 CUBES at (0,0) and (0,1)
		cubes[0][1][i]=1; 
	}
}


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

void zero(){
	//add later
}

void test (){ //makes a 5cm horizontal line and a 5cm line at a 45 degree angle
	moveXYMM()
}

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
