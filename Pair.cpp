#include "Pair.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace
{
    void checkNumber(double value, const char* name)
    {
        if (!isfinite(value))
            throw invalid_argument(string(name) + " must be a finite number");
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

Pair::Pair() : first(0), second(0)
{
}

Pair::Pair(double first, double second) : first(0), second(0)
{
    Init(first, second);
}

void Pair::setFirst(double first)
{
    checkNumber(first, "first");
    this->first = first;
}

void Pair::setSecond(double second)
{
    checkNumber(second, "second");
    this->second = second;
}

void Pair::Init(double first, double second)
{
    checkNumber(first, "first");
    checkNumber(second, "second");
    setFirst(first);
    setSecond(second);
}

void Pair::Read()
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

void Pair::Display() const
{
    cout << "first  = " << first << endl;
    cout << "second = " << second << endl;
}

string Pair::toString() const
{
    ostringstream out;
    out << "(first = " << first << ", second = " << second << ")";
    return out.str();
}

bool Pair::Equal(const Pair& other) const
{
    return first == other.first && second == other.second;
}

bool Pair::Greater(const Pair& other) const
{
    return (first > other.first)
        || (first == other.first && second > other.second);
}