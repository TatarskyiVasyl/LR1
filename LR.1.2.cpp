#ifdef _WIN32
#define _HAS_STD_BYTE 0
#include <Windows.h>
#endif

#include "Pair.h"
#include "Fraction.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Pair makePair(int first, int second)
{
    Pair p;
    p.Init(first, second);
    return p;
}

Fraction makeFraction(int intPart, int fracPart)
{
    Fraction fr;
    if (!fr.Init(intPart, fracPart))
    {
        cout << "Помилка: дробова частина має бути в межах 0..999!" << endl;
        exit(1);
    }
    return fr;
}

int main()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "=== Клас Pair ===" << endl;

    Pair p1 = makePair(3, 5);
    Pair p2;
    p2.Read();

    p1.Display();
    p2.Display();

    if (p1 > p2)   cout << "p1 >  p2" << endl;
    if (p1 < p2)   cout << "p1 <  p2" << endl;
    if (p1 == p2)  cout << "p1 == p2" << endl;
    if (p1 != p2)  cout << "p1 != p2" << endl;
    if (p1 >= p2)  cout << "p1 >= p2" << endl;
    if (p1 <= p2)  cout << "p1 <= p2" << endl;

    cout << endl << "=== Клас Fraction ===" << endl;

    Fraction f1 = makeFraction(2, 500);
    Fraction f2;
    f2.Read();

    f1.Display();
    f2.Display();

    if (f1 > f2)   cout << "f1 >  f2" << endl;
    if (f1 < f2)   cout << "f1 <  f2" << endl;
    if (f1 == f2)  cout << "f1 == f2" << endl;
    if (f1 != f2)  cout << "f1 != f2" << endl;
    if (f1 >= f2)  cout << "f1 >= f2" << endl;
    if (f1 <= f2)  cout << "f1 <= f2" << endl;

    return 0;
}