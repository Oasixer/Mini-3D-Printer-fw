/*

Group 414
3D Printer
Math Library

*/

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

float constrain(float value, float min, float max)
{
	value = min(value, max);
	value = max(value, min);
	return value;
}