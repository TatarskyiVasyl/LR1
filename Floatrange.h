#pragma once

class FloatRange
{
private:
	double first;
	double second;

public:
	double GetFirst() const { return first; }
	double GetSecond() const { return second; }
	void SetFirst(double value);
	bool SetSecond(double value);

	bool Init(double x, double y);
	void Display() const;
	void Read();

	bool rangeCheck(double value) const;
};