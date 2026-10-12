#pragma once
#include <string>

class Triangle
{
public:
    class Angle
    {
    private:
        int grades = 0;
        int minutes = 0;

        bool setTotalMinutes(int total);

    public:
        static constexpr int MAX_GRADES = 100000;

        int getGrades() const { return grades; }
        int getMinutes() const { return minutes; }
        int getTotalMinutes() const { return grades * 60 + minutes; }

        bool setGrades(int value);
        bool setMinutes(int value);

        bool        Init(int grades, int minutes);
        void        Read();
        void        Display() const;
        std::string toString() const;

        double toRadians() const;
        double toDegrees() const;
        void   Normalize();
        bool   Increase(const Angle& delta);
        bool   Decrease(const Angle& delta);
        double Sin() const;

        bool Equal(const Angle& other) const;
        bool NotEqual(const Angle& other) const { return !Equal(other); }
        bool Greater(const Angle& other) const;
        bool GreaterOrEqual(const Angle& other) const { return !Less(other); }
        bool Less(const Angle& other) const;
        bool LessOrEqual(const Angle& other) const { return !Greater(other); }
    };

private:
    double a = 1, b = 1, c = 1;
    Angle  A, B, C;

    bool apply(double newA, double newB, double newC, int fixedIndex, int fixedMinutes);

public:
    static constexpr double MIN_SIDE = 1e-9;
    static constexpr double MAX_SIDE = 1e9;

    Triangle();

    double getSideA() const { return a; }
    double getSideB() const { return b; }
    double getSideC() const { return c; }
    Angle  getAngleA() const { return A; }
    Angle  getAngleB() const { return B; }
    Angle  getAngleC() const { return C; }

    bool setSideA(double value);
    bool setSideB(double value);
    bool setSideC(double value);
    bool setAngleA(const Angle& value);
    bool setAngleB(const Angle& value);
    bool setAngleC(const Angle& value);

    bool        Init(double a, double b, double c);
    void        Read();
    void        Display() const;
    std::string toString() const;

    double Area() const;
    double Perimeter() const;
    double HeightA() const;
    double HeightB() const;
    double HeightC() const;

    bool        IsEquilateral() const;
    bool        IsIsosceles() const;
    bool        IsRight() const;
    std::string TypeToString() const;
};
