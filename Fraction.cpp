#include "Fraction.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace
{
    const long long MAX_WHOLE = 1LL << 53;

    void checkWhole(long long whole)
    {
        if (whole > MAX_WHOLE || whole < -MAX_WHOLE)
            throw invalid_argument("whole part must not exceed 2^53 by absolute value");
    }

    void checkFrac(double frac)
    {
        if (!(frac >= 0.0 && frac < 1.0))
            throw invalid_argument("fractional part must be in range [0; 1)");
    }

    void checkPair(const Pair& p)
    {
        double whole = p.getFirst();
        if (whole != floor(whole))
            throw invalid_argument("whole part must be an integer");
        if (fabs(whole) > static_cast<double>(MAX_WHOLE))
            throw invalid_argument("whole part must not exceed 2^53 by absolute value");
        checkFrac(p.getSecond());
    }
}

Fraction::Fraction() : pair(0, 0)
{
}

Fraction::Fraction(long long whole, double frac) : pair(0, 0)
{
    Init(whole, frac);
}

Fraction Fraction::FromDouble(double value)
{
    if (!isfinite(value))
        throw invalid_argument("value must be a finite number");
    double whole = floor(value);
    double frac = value - whole;
    if (frac >= 1.0)
    {
        whole += 1.0;
        frac = 0.0;
    }
    checkWhole(static_cast<long long>(whole));
    return Fraction(static_cast<long long>(whole), frac);
}

void Fraction::setPair(const Pair& pair)
{
    checkPair(pair);
    this->pair = pair;
}

void Fraction::setWhole(long long whole)
{
    checkWhole(whole);
    Pair p = pair;
    p.setFirst(static_cast<double>(whole));
    setPair(p);
}

void Fraction::setFrac(double frac)
{
    checkFrac(frac);
    Pair p = pair;
    p.setSecond(frac);
    setPair(p);
}

void Fraction::Init(long long whole, double frac)
{
    checkWhole(whole);
    checkFrac(frac);
    setPair(Pair(static_cast<double>(whole), frac));
}
    void Fraction::Read()
{
    cout << endl;
    cout << "Fraction: first = whole part (integer), second = fractional part from [0; 1)" << endl;
    while (true)
    {
        Pair p;
        p.Read();
        try
        {
            setPair(p);
            return;
        }
        catch (const invalid_argument& e)
        {
            cout << "Error: " << e.what() << ". Try again." << endl;
        }
    }
}

void Fraction::Display() const
{
    cout << "pair = " << endl;
    pair.Display();
    cout << "value = " << toDouble() << endl;
}

string Fraction::toString() const
{
    ostringstream out;
    out.precision(15);
    out << "Fraction[whole = " << getWhole() << ", frac = " << getFrac()
        << ", value = " << toDouble() << "]";
    return out.str();
}
