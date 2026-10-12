#include "Triangle.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
using namespace std;

namespace
{
    const double kAnglePi = 3.14159265358979323846;
    const int    kMinutesInCircle = 360 * 60;

    bool isValidAngle(int grades, int minutes)
    {
        return grades >= -Triangle::Angle::MAX_GRADES && grades <= Triangle::Angle::MAX_GRADES
            && minutes >= 0 && minutes <= 59;
    }

    const double kRelativeTolerance = 1e-9;
    const int    kStraightMinutes = 180 * 60;

    bool isValidSide(double s)
    {
        return isfinite(s) && s >= Triangle::MIN_SIDE && s <= Triangle::MAX_SIDE;
    }

    bool almostEqual(double x, double y)
    {
        return fabs(x - y) <= kRelativeTolerance * max(fabs(x), fabs(y));
    }

    double oppositeSide(double s1, double s2, int angleMinutes)
    {
        double scale = max(s1, s2);
        double x = s1 / scale, y = s2 / scale;
        double half = sin(angleMinutes * (kAnglePi / (180.0 * 60.0)) / 2.0);
        return scale * sqrt((x - y) * (x - y) + 4.0 * x * y * half * half);
    }

    bool computeAngles(double a, double b, double c, int fixedIndex, int fixedMinutes, int out[3])
    {
        double scale = max(a, max(b, c));
        double x = a / scale, y = b / scale, z = c / scale;

        double cosines[3] = { (y * y + z * z - x * x) / (2 * y * z),
                              (x * x + z * z - y * y) / (2 * x * z),
                              (x * x + y * y - z * z) / (2 * x * y) };

        double exact[3];
        for (int i = 0; i < 3; i++)
        {
            double cs = min(1.0, max(-1.0, cosines[i]));
            exact[i] = acos(cs) * (kStraightMinutes / kAnglePi);
        }
        if (fixedIndex >= 0)
            exact[fixedIndex] = fixedMinutes;
        else
        {
            int equalIndex = -1, otherIndex = -1;
            if (almostEqual(a, b) && almostEqual(b, c)) { out[0] = out[1] = out[2] = kStraightMinutes / 3; return true; }
            if (almostEqual(a, b)) { equalIndex = 0; otherIndex = 2; }
            else if (almostEqual(b, c)) { equalIndex = 1; otherIndex = 0; }
            else if (almostEqual(a, c)) { equalIndex = 0; otherIndex = 1; }
            if (equalIndex >= 0)
            {
                int base = static_cast<int>(floor(exact[equalIndex] + 0.5));
                int apex = kStraightMinutes - 2 * base;
                if (base < 1 || apex < 1)
                    return false;
                for (int i = 0; i < 3; i++)
                    out[i] = (i == otherIndex) ? apex : base;
                return true;
            }
        }

        int    floors[3];
        double remainder[3];
        int    sum = 0;
        for (int i = 0; i < 3; i++)
        {
            floors[i] = static_cast<int>(floor(exact[i]));
            remainder[i] = exact[i] - floors[i];
            sum += floors[i];
        }

        int deficit = kStraightMinutes - sum;
        int order[3] = { 0, 1, 2 };
        sort(order, order + 3, [&](int p, int q) { return remainder[p] > remainder[q]; });
        for (int k = 0; k < 3 && deficit > 0; k++)
        {
            if (order[k] == fixedIndex)
                continue;
            floors[order[k]]++;
            deficit--;
        }
        if (deficit != 0)
            return false;

        for (int i = 0; i < 3; i++)
        {
            if (floors[i] < 1 || floors[i] > kStraightMinutes - 1)
                return false;
            out[i] = floors[i];
        }
        return true;
    }

    double readDouble(const string& prompt, bool& eof)
    {
        double value;
        while (true)
        {
            cout << prompt;
            if (cin >> value)
                return value;
            if (cin.eof())
            {
                cin.clear();
                eof = true;
                return 0;
            }
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "Error: enter a number!" << endl;
        }
    }
}

bool Triangle::Angle::setGrades(int value)
{
    if (!isValidAngle(value, minutes))
        return false;
    grades = value;
    return true;
}

bool Triangle::Angle::setMinutes(int value)
{
    if (!isValidAngle(grades, value))
        return false;
    minutes = value;
    return true;
}

bool Triangle::Angle::Init(int grades, int minutes)
{
    if (!isValidAngle(grades, minutes))
        return false;
    this->grades = grades;
    this->minutes = minutes;
    return true;
}

bool Triangle::Angle::setTotalMinutes(int total)
{
    int g = total / 60;
    int m = total % 60;
    if (m < 0)
    {
        m += 60;
        g -= 1;
    }
    return Init(g, m);
}

void Triangle::Angle::Read()
{
    while (true)
    {
        int g, m;
        cout << "grades  = ? ";
        bool ok = static_cast<bool>(cin >> g);
        if (ok)
        {
            cout << "minutes = ? ";
            ok = static_cast<bool>(cin >> m);
        }

        if (!ok)
        {
            if (cin.eof())
            {
                cin.clear();
                return;
            }
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "Error: enter integer numbers!" << endl;
            continue;
        }

        if (Init(g, m))
            return;
        cout << "Error: grades must be in [-100000; 100000], minutes in [0; 59]!" << endl;
    }
}

void Triangle::Angle::Display() const
{
    cout << "grades  = " << grades << endl;
    cout << "minutes = " << minutes << endl;
    cout << "angle   = " << toString() << endl;
}

string Triangle::Angle::toString() const
{
    int total = getTotalMinutes();
    ostringstream out;
    if (total < 0)
    {
        out << '-';
        total = -total;
    }
    out << total / 60 << " deg " << total % 60 << " min";
    return out.str();
}

double Triangle::Angle::toRadians() const
{
    return getTotalMinutes() * (kAnglePi / (180.0 * 60.0));
}

double Triangle::Angle::toDegrees() const
{
    return getTotalMinutes() / 60.0;
}

void Triangle::Angle::Normalize()
{
    int r = getTotalMinutes() % kMinutesInCircle;
    if (r < 0)
        r += kMinutesInCircle;
    setTotalMinutes(r);
}

bool Triangle::Angle::Increase(const Angle& delta)
{
    return setTotalMinutes(getTotalMinutes() + delta.getTotalMinutes());
}

bool Triangle::Angle::Decrease(const Angle& delta)
{
    return setTotalMinutes(getTotalMinutes() - delta.getTotalMinutes());
}

double Triangle::Angle::Sin() const
{
    int r = getTotalMinutes() % kMinutesInCircle;
    if (r > kMinutesInCircle / 2)
        r -= kMinutesInCircle;
    else if (r < -kMinutesInCircle / 2)
        r += kMinutesInCircle;
    if (r > kMinutesInCircle / 4)
        r = kMinutesInCircle / 2 - r;
    else if (r < -kMinutesInCircle / 4)
        r = -kMinutesInCircle / 2 - r;
    return sin(r * (kAnglePi / (180.0 * 60.0)));
}

bool Triangle::Angle::Equal(const Angle& other) const
{
    return getTotalMinutes() == other.getTotalMinutes();
}

bool Triangle::Angle::Greater(const Angle& other) const
{
    return getTotalMinutes() > other.getTotalMinutes();
}

bool Triangle::Angle::Less(const Angle& other) const
{
    return getTotalMinutes() < other.getTotalMinutes();
}

Triangle::Triangle()
{
    apply(1, 1, 1, -1, 0);
}

bool Triangle::apply(double newA, double newB, double newC, int fixedIndex, int fixedMinutes)
{
    if (!isValidSide(newA) || !isValidSide(newB) || !isValidSide(newC))
        return false;
    if (!(newA < newB + newC && newB < newA + newC && newC < newA + newB))
        return false;

    int minutes[3];
    if (!computeAngles(newA, newB, newC, fixedIndex, fixedMinutes, minutes))
        return false;

    a = newA;
    b = newB;
    c = newC;
    A.Init(minutes[0] / 60, minutes[0] % 60);
    B.Init(minutes[1] / 60, minutes[1] % 60);
    C.Init(minutes[2] / 60, minutes[2] % 60);
    return true;
}

bool Triangle::setSideA(double value) { return apply(value, b, c, -1, 0); }
bool Triangle::setSideB(double value) { return apply(a, value, c, -1, 0); }
bool Triangle::setSideC(double value) { return apply(a, b, value, -1, 0); }

bool Triangle::setAngleA(const Angle& value)
{
    int t = value.getTotalMinutes();
    if (t < 1 || t > kStraightMinutes - 1 || !isValidSide(b) || !isValidSide(c))
        return false;
    return apply(oppositeSide(b, c, t), b, c, 0, t);
}

bool Triangle::setAngleB(const Angle& value)
{
    int t = value.getTotalMinutes();
    if (t < 1 || t > kStraightMinutes - 1)
        return false;
    return apply(a, oppositeSide(a, c, t), c, 1, t);
}

bool Triangle::setAngleC(const Angle& value)
{
    int t = value.getTotalMinutes();
    if (t < 1 || t > kStraightMinutes - 1)
        return false;
    return apply(a, b, oppositeSide(a, b, t), 2, t);
}

bool Triangle::Init(double a, double b, double c)
{
    return apply(a, b, c, -1, 0);
}

void Triangle::Read()
{
    while (true)
    {
        bool eof = false;
        double x = readDouble("a = ? ", eof);
        double y = eof ? 0 : readDouble("b = ? ", eof);
        double z = eof ? 0 : readDouble("c = ? ", eof);
        if (eof)
            return;

        if (Init(x, y, z))
            return;
        cout << "Error: such a triangle does not exist (sides must be in [1e-9; 1e9], "
            "each less than the sum of the other two, every angle at least 1 minute)!" << endl;
    }
}

void Triangle::Display() const
{
    cout << "side a  = " << a << endl;
    cout << "side b  = " << b << endl;
    cout << "side c  = " << c << endl;
    cout << "angle A = " << A.toString() << endl;
    cout << "angle B = " << B.toString() << endl;
    cout << "angle C = " << C.toString() << endl;
}

string Triangle::toString() const
{
    ostringstream out;
    out << "Triangle[a=" << a << ", b=" << b << ", c=" << c
        << ", A=" << A.toString() << ", B=" << B.toString() << ", C=" << C.toString() << "]";
    return out.str();
}

double Triangle::Area() const
{
    double s[3] = { a, b, c };
    sort(s, s + 3, greater<double>());
    double x = s[0], y = s[1], z = s[2];
    return 0.25 * sqrt((x + (y + z)) * (z - (x - y)) * (z + (x - y)) * (x + (y - z)));
}

double Triangle::Perimeter() const
{
    return a + b + c;
}

double Triangle::HeightA() const { return 2 * Area() / a; }
double Triangle::HeightB() const { return 2 * Area() / b; }
double Triangle::HeightC() const { return 2 * Area() / c; }

bool Triangle::IsEquilateral() const
{
    return almostEqual(a, b) && almostEqual(b, c);
}

bool Triangle::IsIsosceles() const
{
    return almostEqual(a, b) || almostEqual(b, c) || almostEqual(a, c);
}

bool Triangle::IsRight() const
{
    double s[3] = { a, b, c };
    sort(s, s + 3);
    double longest2 = s[2] * s[2];
    return fabs(longest2 - s[0] * s[0] - s[1] * s[1]) <= kRelativeTolerance * longest2;
}

string Triangle::TypeToString() const
{
    if (IsEquilateral())
        return "equilateral";
    if (IsIsosceles())
        return IsRight() ? "isosceles right" : "isosceles";
    return IsRight() ? "right" : "scalene";
}
