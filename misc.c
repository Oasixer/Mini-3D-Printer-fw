/*

Group 414
3D Printer
Misc Library

*/
#ifndef MISC_C
#define MISC_C

float max(float number1, float number2)
{
  if (number1 > number2)
    return number1;
  return number2;
}

float min(float number1, float number2)
{
  if (number1 < number2)
    return number1;
  return number2;
}

float constrain(float value, float minim, float maxim)
{
  value = min(value, maxim);
  value = max(value, minim);
  return value;
}

void waitForEnter(){
  while (!getButtonPress(buttonEnter)){}
  while (getButtonPress(buttonEnter)){}
}

void display(int line, float x, float y)
{
  displayString(line, "(%f, %f)", x, y);
}

#endif
