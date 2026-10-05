#pragma once
#include <string>

class FractionC
{
private:
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

    Pair pair;

public:
    FractionC();
    FractionC(long long whole, double frac);

    static FractionC FromDouble(double value);

    FractionC::Pair getPair() const { return pair; }
    long long getWhole() const { return static_cast<long long>(pair.getFirst()); }
    double getFrac() const { return pair.getSecond(); }

    void setPair(const FractionC::Pair& pair);
    void setWhole(long long whole);
    void setFrac(double frac);

    void Init(long long whole, double frac);
    void Read();
    void Display() const;
    std::string toString() const;
    double toDouble() const { return pair.getFirst() + pair.getSecond(); }

    bool Equal(const FractionC& other) const { return pair.Equal(other.pair); }
    bool NotEqual(const FractionC& other) const { return pair.NotEqual(other.pair); }
    bool Greater(const FractionC& other) const { return pair.Greater(other.pair); }
    bool GreaterOrEqual(const FractionC& other) const { return pair.GreaterOrEqual(other.pair); }
    bool Less(const FractionC& other) const { return pair.Less(other.pair); }
    bool LessOrEqual(const FractionC& other) const { return pair.LessOrEqual(other.pair); }
};
