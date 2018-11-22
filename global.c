// by Zachariah, Kaelan, Lyndon, Daddy Parth

#ifndef GLOBAL_C
#define GLOBAL_C

const float VELOCITY = 37; //mm/s 200/8

const float TOLERANCE = 0.5;

const float Z_MAX = 80;
const long COOL_DOWN_TIME = 12000 //2 minutes -- might need to be changed

const tMotor motorY = motorA;
const tMotor motorX = motorD;
const tMotor motorZ1 = motorB;
const tMotor motorZ2 = motorC;

const tSensors COLOR_SENSOR = S1;

const tSensors TOUCH_Z = S2;
const tSensors TOUCH_Y = S3;
const tSensors I2C_PORT = S4;


const float ENC_TO_MM=(float)24/360;
const float Z_ENC_TO_MM = 0.0022222;
const float MM_TO_ENC=15;
const float CUBEHEIGHT=5;
const float LAYERHEIGHT=0.7;
const float MAXLAYER=5*(int)(CUBEHEIGHT/LAYERHEIGHT);

float step;//for debugging
int cubes[5][5];

#endif
