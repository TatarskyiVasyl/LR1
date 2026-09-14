#include "FloatRange.h"
#include <iostream>

using namespace std;

void FloatRange::SetFirst(double value)
{
	first = value;
}

bool FloatRange::SetSecond(double value)
{
	if (value > first)
	{
		second = value;
		return true;
	}
	else
	{
		second = first + 1.0;
		return false;
	}
}

bool FloatRange::Init(double x, double y)
{
	SetFirst(x);
	return SetSecond(y);
}

void FloatRange::Display() const
{
	cout << "[" << first << ", " << second << "]" << endl;
}

void FloatRange::Read()
{
	double x, y;
	cout << "first = ? ";
	cin >> x;
	do {
		cout << "second = ? ";
		cin >> y;
	} while (!Init(x, y));
}

bool FloatRange::rangeCheck(double value) const
{
	return (value >= first && value <= second);
}