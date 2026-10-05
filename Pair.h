#pragma once
#include <string>

class Pair
{
private:
    double first;
    double second;

public:
    Pair();
    Pair(double first, double second);

    double getFirst() const { return first; }
    double getSecond() const { return second; }
    void setFirst(double first);
    void setSecond(double second);

    void Init(double first, double second);
    void Read();
    void Display() const;
    std::string toString() const;

    bool Equal(const Pair& other) const;
    bool NotEqual(const Pair& other) const { return !Equal(other); }
    bool Greater(const Pair& other) const;
    bool GreaterOrEqual(const Pair& other) const { return Greater(other) || Equal(other); }
    bool Less(const Pair& other) const { return other.Greater(*this); }
    bool LessOrEqual(const Pair& other) const { return Less(other) || Equal(other); }
};
