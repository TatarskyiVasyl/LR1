#include "Angle.h"
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
        return grades >= -Angle::MAX_GRADES && grades <= Angle::MAX_GRADES
            && minutes >= 0 && minutes <= 59;
    }
}

bool Angle::setGrades(int value)
{
    if (!isValidAngle(value, minutes))
        return false;
    grades = value;
    return true;
}

bool Angle::setMinutes(int value)
{
    if (!isValidAngle(grades, value))
        return false;
    minutes = value;
    return true;
}

bool Angle::Init(int grades, int minutes)
{
    if (!isValidAngle(grades, minutes))
        return false;
    this->grades = grades;
    this->minutes = minutes;
    return true;
}

bool Angle::setTotalMinutes(int total)
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

void Angle::Read()
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

void Angle::Display() const
{
    cout << "grades  = " << grades << endl;
    cout << "minutes = " << minutes << endl;
    cout << "angle   = " << toString() << endl;
}

string Angle::toString() const
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

double Angle::toRadians() const
{
    return getTotalMinutes() * (kAnglePi / (180.0 * 60.0));
}

double Angle::toDegrees() const
{
    return getTotalMinutes() / 60.0;
}

void Angle::Normalize()
{
    int r = getTotalMinutes() % kMinutesInCircle;
    if (r < 0)
        r += kMinutesInCircle;
    setTotalMinutes(r);
}

bool Angle::Increase(const Angle& delta)
{
    return setTotalMinutes(getTotalMinutes() + delta.getTotalMinutes());
}

bool Angle::Decrease(const Angle& delta)
{
    return setTotalMinutes(getTotalMinutes() - delta.getTotalMinutes());
}

double Angle::Sin() const
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

bool Angle::Equal(const Angle& other) const
{
    return getTotalMinutes() == other.getTotalMinutes();
}

bool Angle::Greater(const Angle& other) const
{
    return getTotalMinutes() > other.getTotalMinutes();
}

bool Angle::Less(const Angle& other) const
{
    return getTotalMinutes() < other.getTotalMinutes();
}
