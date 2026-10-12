#include "Triangle.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

using Angle = Triangle::Angle;

static void Report(const string& what, bool accepted)
{
    cout << what << ": " << (accepted ? "accepted" : "rejected") << endl;
}

static Angle MakeAngle(int grades, int minutes)
{
    Angle a;
    if (!a.Init(grades, minutes))
        cout << "MakeAngle: wrong value, zero angle returned" << endl;
    return a;
}

static void PrintComparison(const Angle& x, const Angle& y)
{
    cout << boolalpha;
    cout << x.toString() << " vs " << y.toString() << endl;
    cout << "   Equal          : " << x.Equal(y) << endl;
    cout << "   NotEqual       : " << x.NotEqual(y) << endl;
    cout << "   Greater        : " << x.Greater(y) << endl;
    cout << "   GreaterOrEqual : " << x.GreaterOrEqual(y) << endl;
    cout << "   Less           : " << x.Less(y) << endl;
    cout << "   LessOrEqual    : " << x.LessOrEqual(y) << endl;
}

static void DemoAngle()
{
    cout << "================ class Angle ================" << endl;

    cout << endl << "--- creation of objects and arrays ---" << endl;
    Angle a1;
    Angle a2;
    a2.Init(30, 15);
    Angle a3 = a2;
    Angle a4 = MakeAngle(400, 45);
    Angle arr1[3];
    arr1[0].Init(10, 0);
    arr1[1].Init(100, 30);
    arr1[2].Init(-5, 20);
    Angle* pa = new Angle(a2);
    Angle* parr = new Angle[2];
    parr[0].Init(180, 0);
    parr[1] = *pa;
    cout << "a1 (default) = " << a1.toString() << endl;
    cout << "a2 (Init)    = " << a2.toString() << endl;
    cout << "a3 (copy)    = " << a3.toString() << endl;
    cout << "a4 (function)= " << a4.toString() << endl;
    for (int i = 0; i < 3; i++)
        cout << "arr1[" << i << "]     = " << arr1[i].toString() << endl;
    for (int i = 0; i < 2; i++)
        cout << "parr[" << i << "]     = " << parr[i].toString() << endl;
    delete pa;
    delete[] parr;

    cout << endl << "--- Display, getters, setters ---" << endl;
    a2.Display();
    cout << "getGrades() = " << a2.getGrades() << ", getMinutes() = " << a2.getMinutes()
        << ", getTotalMinutes() = " << a2.getTotalMinutes() << endl;
    Report("a2.setGrades(45)      ", a2.setGrades(45));
    Report("a2.setMinutes(59)     ", a2.setMinutes(59));
    Report("a2.setMinutes(60)     ", a2.setMinutes(60));
    Report("a2.setGrades(100001)  ", a2.setGrades(100001));
    Report("a2.Init(10, -1)       ", a2.Init(10, -1));
    cout << "a2 after rejected calls = " << a2.toString() << endl;

    cout << endl << "--- conversion to radians ---" << endl;
    Angle straight = MakeAngle(180, 0), right = MakeAngle(90, 0), small = MakeAngle(0, 30);
    cout << setprecision(10);
    cout << straight.toString() << " = " << straight.toRadians() << " rad (" << straight.toDegrees() << " deg)" << endl;
    cout << right.toString() << "  = " << right.toRadians() << " rad (" << right.toDegrees() << " deg)" << endl;
    cout << small.toString() << "   = " << small.toRadians() << " rad (" << small.toDegrees() << " deg)" << endl;

    cout << endl << "--- reduction to the range 0 - 360 ---" << endl;
    Angle big = MakeAngle(725, 10), negative;
    negative.Init(-1, 30);
    cout << big.toString() << " -> ";
    big.Normalize();
    cout << big.toString() << endl;
    cout << negative.toString() << " -> ";
    negative.Normalize();
    cout << negative.toString() << endl;

    cout << endl << "--- increase and decrease ---" << endl;
    Angle x = MakeAngle(350, 40), delta = MakeAngle(20, 30);
    Report("x.Increase(20 deg 30 min)", x.Increase(delta));
    cout << "x = " << x.toString() << endl;
    Report("x.Decrease(20 deg 30 min)", x.Decrease(delta));
    cout << "x = " << x.toString() << endl;
    Angle y = MakeAngle(0, 10), d2 = MakeAngle(0, 20);
    Report("y.Decrease(0 deg 20 min)", y.Decrease(d2));
    cout << "y = " << y.toString() << " (angles below zero are allowed)" << endl;
    Angle edge = MakeAngle(Angle::MAX_GRADES, 0), one = MakeAngle(1, 0);
    Report("edge.Increase(1 deg)  ", edge.Increase(one));
    cout << "edge = " << edge.toString() << " (unchanged)" << endl;

    cout << endl << "--- sine ---" << endl;
    const int sample[][2] = { { 0, 0 }, { 30, 0 }, { 45, 0 }, { 90, 0 }, { 180, 0 }, { 270, 0 }, { 390, 0 } };
    for (const auto& s : sample)
    {
        Angle t = MakeAngle(s[0], s[1]);
        cout << "sin(" << t.toString() << ") = " << t.Sin() << endl;
    }

    cout << endl << "--- comparison ---" << endl;
    PrintComparison(MakeAngle(10, 30), MakeAngle(10, 45));
    PrintComparison(MakeAngle(10, 30), MakeAngle(10, 30));
    PrintComparison(MakeAngle(100, 0), MakeAngle(99, 59));

    Angle best = arr1[0];
    for (int i = 1; i < 3; i++)
        if (arr1[i].Greater(best))
            best = arr1[i];
    cout << "largest angle in arr1 = " << best.toString() << endl;

    cout << endl << "--- Read from keyboard ---" << endl;
    Angle r;
    r.Read();
    r.Display();
}

static void DemoTriangle()
{
    cout << endl << "================ class Triangle ================" << endl;

    cout << endl << "--- creation of objects and arrays ---" << endl;
    Triangle t1;
    Triangle t2;
    t2.Init(3, 4, 5);
    Triangle t3 = t2;
    Triangle arr[4];
    arr[0].Init(2, 2, 2);
    arr[1].Init(5, 5, 6);
    arr[2].Init(1, 1, 1.4142135623730951);
    arr[3].Init(4, 5, 6);
    Triangle* pt = new Triangle(t2);
    Triangle* parr = new Triangle[2];
    parr[0].Init(7, 8, 9);
    parr[1] = *pt;
    cout << "t1 (default) : " << t1.toString() << endl;
    cout << "t2 (Init)    : " << t2.toString() << endl;
    cout << "t3 (copy)    : " << t3.toString() << endl;
    for (int i = 0; i < 4; i++)
        cout << "arr[" << i << "]       : " << arr[i].toString() << endl;
    for (int i = 0; i < 2; i++)
        cout << "parr[" << i << "]      : " << parr[i].toString() << endl;
    delete pt;
    delete[] parr;

    cout << endl << "--- Init with wrong values ---" << endl;
    Triangle bad = t2;
    Report("Init(1, 2, 3)        ", bad.Init(1, 2, 3));
    Report("Init(1, 1, 3)        ", bad.Init(1, 1, 3));
    Report("Init(-1, 2, 2)       ", bad.Init(-1, 2, 2));
    Report("Init(0, 2, 2)        ", bad.Init(0, 2, 2));
    Report("Init(1, 1, 1.99999999)", bad.Init(1, 1, 1.99999999));
    cout << "bad after rejected calls = " << bad.toString() << endl;

    cout << endl << "--- Display and getters ---" << endl;
    t2.Display();
    cout << "sides: " << t2.getSideA() << ", " << t2.getSideB() << ", " << t2.getSideC() << endl;
    cout << "angles: " << t2.getAngleA().toString() << "; " << t2.getAngleB().toString()
        << "; " << t2.getAngleC().toString() << endl;

    cout << endl << "--- setters ---" << endl;
    Triangle s = t2;
    Report("s.setSideA(4)        ", s.setSideA(4));
    cout << "s = " << s.toString() << endl;
    Report("s.setSideC(100)      ", s.setSideC(100));
    cout << "s = " << s.toString() << endl;
    Angle ninety = MakeAngle(90, 0), zero = MakeAngle(0, 0), straight = MakeAngle(180, 0);
    Report("s.setAngleC(90 deg)  ", s.setAngleC(ninety));
    cout << "s = " << s.toString() << " -> " << s.TypeToString() << endl;
    Report("s.setAngleA(0 deg)   ", s.setAngleA(zero));
    Report("s.setAngleB(180 deg) ", s.setAngleB(straight));
    cout << "s = " << s.toString() << endl;

    cout << endl << "--- area, perimeter, heights, type ---" << endl;
    cout << setprecision(8);
    const char* names[4] = { "arr[0]", "arr[1]", "arr[2]", "arr[3]" };
    for (int i = 0; i < 4; i++)
    {
        const Triangle& t = arr[i];
        cout << names[i] << ": " << t.toString() << endl;
        cout << "   area = " << t.Area() << ", perimeter = " << t.Perimeter() << endl;
        cout << "   heights: hA = " << t.HeightA() << ", hB = " << t.HeightB() << ", hC = " << t.HeightC() << endl;
        cout << boolalpha << "   equilateral: " << t.IsEquilateral() << ", isosceles: " << t.IsIsosceles()
            << ", right: " << t.IsRight() << " -> " << t.TypeToString() << endl;
    }

    cout << endl << "--- Read from keyboard ---" << endl;
    Triangle r;
    r.Read();
    r.Display();
    cout << "type: " << r.TypeToString() << ", area = " << r.Area() << endl;
}

int main()
{
    DemoAngle();
    DemoTriangle();
    return 0;
}
