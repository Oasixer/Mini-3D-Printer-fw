// by Zachariah, Kaelan, Lyndon, Daddy Parth
const int velocity = 25; //mm/s 200/8
const float TOLERANCE = 0.5;
const tMotor motorY = motorA, motorX = motorD;
const tMotor motorZ1 = motorB, motorZ2 = motorC;
float deX, deY, moX,moY, yTar, xTar, xIni, yIni, xCu, yCu, xEn, yEn;
const float ENCTOMM=(float)24/360;
const float MMTOENC=15;
int maxLayer;
int step=0;
