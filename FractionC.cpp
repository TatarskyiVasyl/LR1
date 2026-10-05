#include "FractionC.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace
{
    const long long MAX_WHOLE = 1LL << 53;

    void checkNumber(double value, const char* name)
    {
        if (!isfinite(value))
            throw invalid_argument(string(name) + " must be a finite number");
    }

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

    double readDouble(const string& prompt)
    {
        double value;
        while (true)
        {
            cout << prompt;
            if (cin >> value)
                return value;
            if (cin.eof())
                throw runtime_error("input stream closed");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid number, try again." << endl;
        }
    }
}

FractionC::Pair::Pair() : first(0), second(0)
{
}

FractionC::Pair::Pair(double first, double second) : first(0), second(0)
{
    Init(first, second);
}

void FractionC::Pair::setFirst(double first)
{
    checkNumber(first, "first");
    this->first = first;
}

void FractionC::Pair::setSecond(double second)
{
    checkNumber(second, "second");
    this->second = second;
}

void FractionC::Pair::Init(double first, double second)
{
    checkNumber(first, "first");
    checkNumber(second, "second");
    setFirst(first);
    setSecond(second);
}

void FractionC::Pair::Read()
{
    while (true)
    {
        double first = readDouble("first  = ? ");
        double second = readDouble("second = ? ");
        try
        {
            Init(first, second);
            return;
        }
        catch (const invalid_argument& e)
        {
            cout << "Error: " << e.what() << ". Try again." << endl;
        }
    }
}

void FractionC::Pair::Display() const
{
    cout << "first  = " << first << endl;
    cout << "second = " << second << endl;
}

string FractionC::Pair::toString() const
{
    ostringstream out;
    out << "(first = " << first << ", second = " << second << ")";
    return out.str();
}

bool FractionC::Pair::Equal(const FractionC::Pair& other) const
{
    return first == other.first && second == other.second;
}

bool FractionC::Pair::Greater(const FractionC::Pair& other) const
{
    return (first > other.first)
        || (first == other.first && second > other.second);
}

FractionC::FractionC() : pair(0, 0)
{
}

FractionC::FractionC(long long whole, double frac) : pair(0, 0)
{
    Init(whole, frac);
}

FractionC FractionC::FromDouble(double value)
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
    return FractionC(static_cast<long long>(whole), frac);
}

void FractionC::setPair(const FractionC::Pair& pair)
{
    double whole = pair.getFirst();
    if (whole != floor(whole))
        throw invalid_argument("whole part must be an integer");
    if (fabs(whole) > static_cast<double>(MAX_WHOLE))
        throw invalid_argument("whole part must not exceed 2^53 by absolute value");
    checkFrac(pair.getSecond());

    this->pair = pair;
}

void FractionC::setWhole(long long whole)
{
    checkWhole(whole);
    FractionC::Pair p = pair;
    p.setFirst(static_cast<double>(whole));
    setPair(p);
}

void FractionC::setFrac(double frac)
{
    checkFrac(frac);
    FractionC::Pair p = pair;
    p.setSecond(frac);
    setPair(p);
}

void FractionC::Init(long long whole, double frac)
{
    checkWhole(whole);
    checkFrac(frac);
    setPair(FractionC::Pair(static_cast<double>(whole), frac));
}

void FractionC::Read()
{
    cout << endl;
    cout << "Fraction: first = whole part (integer), second = fractional part from [0; 1)" << endl;
    while (true)
    {
        FractionC::Pair p;
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

void FractionC::Display() const
{
    cout << "pair = " << endl;
    pair.Display();
    cout << "value = " << toDouble() << endl;
}

string FractionC::toString() const
{
    ostringstream out;
    out.precision(15);
    out << "FractionC[whole = " << getWhole() << ", frac = " << getFrac()
        << ", value = " << toDouble() << "]";
    return out.str();
}
