#include "Vector3D.h"
#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

bool Vector3D::setX(double value)
{
    if (!isfinite(value)) return false;
    x = value;
    return true;
}

bool Vector3D::setY(double value)
{
    if (!isfinite(value)) return false;
    y = value;
    return true;
}

bool Vector3D::setZ(double value)
{
    if (!isfinite(value)) return false;
    z = value;
    return true;
}

bool Vector3D::Init(double x, double y, double z)
{
    bool ok = true;
    ok = setX(x) && ok;
    ok = setY(y) && ok;
    ok = setZ(z) && ok;
    return ok;
}

void Vector3D::Read()
{
    double vx, vy, vz;
    cout << endl;
    cout << "x = ? "; cin >> vx;
    cout << "y = ? "; cin >> vy;
    cout << "z = ? "; cin >> vz;
    if (!Init(vx, vy, vz))
        cout << "Помилка: координати вектора мають бути скінченними числами! Значення не змінено." << endl;
}

void Vector3D::Display() const
{
    cout << endl << toString() << endl;
}

string Vector3D::toString() const
{
    ostringstream oss;
    oss << "(" << x << ", " << y << ", " << z << ")";
    return oss.str();
}

Vector3D Vector3D::Add(Vector3D a, Vector3D b)
{
    Vector3D t;
    t.x = a.x + b.x;
    t.y = a.y + b.y;
    t.z = a.z + b.z;
    return t;
}

Vector3D Vector3D::Subtract(Vector3D a, Vector3D b)
{
    Vector3D t;
    t.x = a.x - b.x;
    t.y = a.y - b.y;
    t.z = a.z - b.z;
    return t;
}

double Vector3D::Dot(Vector3D a, Vector3D b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}