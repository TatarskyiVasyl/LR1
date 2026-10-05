#pragma once
#include <string>
#include "Pair.h"

class Fraction
{
private:
    Pair pair;

public:
    Fraction();
    Fraction(long long whole, double frac);

    static Fraction FromDouble(double value);

    Pair getPair() const { return pair; }
    long long getWhole() const { return static_cast<long long>(pair.getFirst()); }
    double getFrac() const { return pair.getSecond(); }

    void setPair(const Pair& pair);
    void setWhole(long long whole);
    void setFrac(double frac);

    void Init(long long whole, double frac);
    void Read();
    void Display() const;
    std::string toString() const;
    double toDouble() const { return pair.getFirst() + pair.getSecond(); }

    bool Equal(const Fraction& other) const { return pair.Equal(other.pair); }
    bool NotEqual(const Fraction& other) const { return pair.NotEqual(other.pair); }
    bool Greater(const Fraction& other) const { return pair.Greater(other.pair); }
    bool GreaterOrEqual(const Fraction& other) const { return pair.GreaterOrEqual(other.pair); }
    bool Less(const Fraction& other) const { return pair.Less(other.pair); }
    bool LessOrEqual(const Fraction& other) const { return pair.LessOrEqual(other.pair); }
};
