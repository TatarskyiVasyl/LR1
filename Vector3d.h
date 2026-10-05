#pragma once
#include <string>
using namespace std;

class Vector3D
{
private:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

public:
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    bool setX(double value);
    bool setY(double value);
    bool setZ(double value);

    bool   Init(double x, double y, double z);
    void   Read();
    void   Display() const;
    string toString() const;

    static Vector3D Add(Vector3D a, Vector3D b);
    static Vector3D Subtract(Vector3D a, Vector3D b);
    static double   Dot(Vector3D a, Vector3D b);
};