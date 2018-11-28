/*
Group 414
3D Printer
Global variables file
*/

#ifndef GLOBAL_C
#define GLOBAL_C

const float VELOCITY = 33; //mm/s 200/8
const float TOLERANCE = 0.5; //mm
const float Z_MAX = 70; //max height, mm
const long COOL_DOWN_TIME = 12000; //time for the heat to dissapate before safe removal

const tMotor motorY = motorA; //motor constants for every axis 
const tMotor motorX = motorD;
const tMotor motorZ1 = motorB; //there are two motors for the z axis
const tMotor motorZ2 = motorC;

const tSensors COLOR_SENSOR = S1; //assign sensor constants
const tSensors TOUCH_Z = S2;
const tSensors TOUCH_Y = S3;
const tSensors I2C_PORT = S4;

const float ENC_TO_MM=(float)24/360; //constant ratio between encoder counts and mm of movement in x and y axis
const float Z_ENC_TO_MM = 0.0022222; //constant ratio between encoder counts and mm of movement in z axis
const float CUBEHEIGHT=5; //max number of stacked cubes that we can print
const float LAYERHEIGHT=0.7; //height in mm of one layer
const float MAXLAYER=5*(int)(CUBEHEIGHT/LAYERHEIGHT); //number of layers in the print

int cubes[5][5]; //cube data: written by scan functions in start.c, read by print.c

#endif
