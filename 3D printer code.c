// by Zachariah, Kaelan, Lyndon, Daddy Parth
const int velocity = 25; //mm/s 200/8
const float encoderCountPermm = 180/PI*4;
const float TOLERANCE = 2;
int motorX = motorA, motorY = motorB, motorZ = motorC, motorE = motorD;

struct Vector {
	float x;
	float y;
	float magnitude;
};

float getMagnitude (struct Vector v)
{
	return sqrt(x*x + y*y);
}

float motorPower (float velocity); //func prototype
/* DEPRECATED MOVEXY FUNCTION (UPDATED ONE BELOW)
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
*/

//kaelans version of moveXY
//changes: 1) take xTarget and yTarget in mm
//2) do all the calculations relative to the starting x and y
//so that we dont lose track of the total movement of the extruder

//this constant needs to be filled in - its the ratio of encoder counts to millimeters
const float ENCTOMMM=24/360;
const float MMTOENC=15;
int maxLayer;

// function prototypes
void moveXYMM (float xTarget, float yTarget, bool rel);
int scanPaper();
int scanColour();
void moveServo(bool input);
void test();
float motorPower(float velocity);

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
	float deltaY = yTarget-yCur; //AHHHH remember to fix indeterminate case below when deltaX or deltaY==0
	if (abs(sqrt(deltaX*deltaX + deltaY*deltaY)) > TOLERANCE)
	{
		// updated function 11/9/18 - 4:25PM
		motor[motorX] = motorPower(velocity / sqrt(deltaX*deltaX + deltaY*deltaY) * deltaX);
		motor[motorY] = motorPower(velocity / sqrt(deltaX*deltaX + deltaY*deltaY) * deltaY);
	}
	
	//motor[motorX] = motorPower((abs(deltaX)/deltaX)*(velocity*(deltaX/sqrt(deltaX*deltaX+deltaY*deltaY))));
	//motor[motorY] = motorPower((abs(deltaY)/deltaY)*(velocity*(deltaY/sqrt(deltaX*deltaX+deltaY*deltaY))));
	while (abs(xTarget - xCur) > TOLERANCE || abs(yTarget - yCur) > TOLERANCE){
		xCur=nMotorEncoder[motorX]*ENCTOMMM-xInit;
		yCur=nMotorEncoder[motorY]*ENCTOMMM-yInit;
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
	maxLayer=0;
	int cubes[5][5][210]=scanPaper();
	boolean printing=false; //temp, use a button press or something
	while (printing){
		for (int lay=0; lay<maxLayer+1; lay++){ //loop through layers
			for (int x=0; x<5; x++){ //loop through columns (x)
				for (int y=0; y<5; y++){ //loop h
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
	int cubes[5][5][210]={0};
	for (int x=0;x<6;x++){
		for(int y=0;y<6;y++){
			moveXYMM(x*15,y*15,false);
				int height=scanPaper();
			if (height>maxLayer)
				maxLayer=height;
			for (int lay=0;lay<height;lay++)
				cubes[x][y][lay]=1;
		}
	}
}

int scanColour(){
	SensorType[S1]=sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S1]=modeEV3Color_Color;
	wait1Msec(50);

	int values[3]={0}; //store 3 colour values
	do{ //loop until all 3 colour values are the same (aka make sure you dont read the wrong colour)
		values[0]=SensorValue[S1];
		wait1Msec(50);
		values[1]=SensorValue[S1];
		wait1Msec(50);
		values[2]=SensorValue[S1];
		wait1Msec(50);
	} while (!(values[0]==values[1]&&values[0]==values[2]))
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

void moveServo (bool input){
	if (input){
		setServoPosition(S4, 1, 25);// extrude on
	}
	else {
		setServoPosition(S4, 1, 0);//extrude off
	}
}

void test (){ //makes a 5cm horizontal line and a 5cm line at a 45 degree angle
	moveXYMM(0,5,true);
	moveXYMM(5,5,true);
}

//this is written but needs testing data to assign values
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
