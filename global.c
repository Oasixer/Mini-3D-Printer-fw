// by Zachariah, Kaelan, Lyndon, Daddy Parth

#IFNDEF GLOBAL_C
#DEFINE GLOBAL_C

const int VELOCITY = 25; //mm/s 200/8
const float TOLERANCE = 0.5;
const tMotor motorY = motorA;
const tMotor motorX = motorD;
const tMotor motorZ1 = motorB;
const tMotor motorZ2 = motorC;
const tSensors COLOR_SENSOR = S1;
const tSensors TOUCH_Z = S2;
const tSensors TOUCH_Y = S3;
const tSensors I2C_PORT = S4;
float deltaX, deltaY, powerX, powerY, powerZ, yTar, xTar, xCurrent, yCurrent;
const float ENC_TO_MM=(float)24/360;
const float MM_TO_ENC=15;
const float LAYERHEIGHT=0.5;
const float MAXLAYER=5*LAYERHEIGHT;
float step;//for debugging
int cubes[5][5];

#ENDIF