#include <iostream>
#include "FloatRange.h"
#include <Windows.h>

using namespace std;

FloatRange makeFloatRange(double x, double y)
{
	FloatRange rr;
	if (!rr.Init(x, y))
		cout << "wrong argument to Init (second)" << endl;
	return rr;
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	FloatRange r;
	r.Init(0.0, 10.0);
	r.Display();

	cout << (r.rangeCheck(5.0) ? "5 входить у діапазон" : "5 не входить у діапазон") << endl;
	cout << (r.rangeCheck(10.0) ? "10 входить у діапазон" : "10 не входить у діапазон") << endl;
	cout << (r.rangeCheck(10.1) ? "10.1 входить у діапазон" : "10.1 не входить у діапазон") << endl;

	FloatRange k;
	k.Read();
	k.Display();

	FloatRange i;
	double a, b;
	cout << "first = ? ";
	cin >> a;
	cout << "second = ? ";
	cin >> b;
	i = makeFloatRange(a, b);
	i.Display();

	return 0;
}