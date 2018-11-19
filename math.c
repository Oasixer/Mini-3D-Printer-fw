/*

Group 414
3D Printer
Math Library

*/
#ifndef MATH_C
#define MATH_C

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

#endif
