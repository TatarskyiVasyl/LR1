#pragma once
#include <string>

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
