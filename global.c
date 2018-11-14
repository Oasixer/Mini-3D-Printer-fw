// by Zachariah, Kaelan, Lyndon, Daddy Parth
const int VELOCITY = 25; //mm/s 200/8
const float TOLERANCE = 0.5;
const tMotor motorY = motorA, motorX = motorD;
const tMotor motorZ1 = motorB, motorZ2 = motorC;
const tSensors COLOR_SENSOR = S1, TOUCH_Z = S2; TOUCH_Y = S3;
const tSensors I2C_PORT = S4;
float deltaX, deltaY, powerX, powerY, yTar, xTar, xCurrent, yCurrent;
const float ENC_TO_MM=(float)24/360;
const float MM_TO_ENC=15;
const float LAYERHEIGHT=0.5;
const float MAXLAYER=5*LAYERHEIGHT;
float step;//for debugging
int cubes[5][5];
