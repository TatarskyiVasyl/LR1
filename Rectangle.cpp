#include "Rectangle.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace
{
    void validate(double x, double y, double width, double height)
    {
        if (!isfinite(x))
            throw invalid_argument("x must be a finite number");
        if (!isfinite(y))
            throw invalid_argument("y must be a finite number");
        if (!isfinite(width) || width <= 0)
            throw invalid_argument("width must be a finite number greater than 0");
        if (!isfinite(height) || height <= 0)
            throw invalid_argument("height must be a finite number greater than 0");
        if (!isfinite(x + width) || !isfinite(y + height))
            throw invalid_argument("rectangle is too large (coordinates overflow)");
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

Rectangle::Rectangle() : x(0), y(0), width(1), height(1)
{
}

Rectangle::Rectangle(double x, double y, double width, double height)
    : x(0), y(0), width(1), height(1)
{
    Init(x, y, width, height);
}

void Rectangle::setX(double x)
{
    validate(x, y, width, height);
    this->x = x;
}

void Rectangle::setY(double y)
{
    validate(x, y, width, height);
    this->y = y;
}

void Rectangle::setWidth(double width)
{
    validate(x, y, width, height);
    this->width = width;
}

void Rectangle::setHeight(double height)
{
    validate(x, y, width, height);
    this->height = height;
}

void Rectangle::Init(double x, double y, double width, double height)
{
    validate(x, y, width, height);
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Rectangle::Read()
{
    while (true)
    {
        cout << endl;
        double x = readDouble("x      = ? ");
        double y = readDouble("y      = ? ");
        double width = readDouble("width  = ? ");
        double height = readDouble("height = ? ");
        try
        {
            Init(x, y, width, height);
            return;
        }
        catch (const invalid_argument& e)
        {
            cout << "Error: " << e.what() << ". Try again." << endl;
        }
    }
}

void Rectangle::Display() const
{
    cout << endl;
    cout << "x      = " << x << endl;
    cout << "y      = " << y << endl;
    cout << "width  = " << width << endl;
    cout << "height = " << height << endl;
}

string Rectangle::toString() const
{
    ostringstream out;
    out << "Rectangle[x=" << x << ", y=" << y
        << ", width=" << width << ", height=" << height << "]";
    return out.str();
}

void Rectangle::Move(double dx, double dy)
{
    double newX = x + dx;
    double newY = y + dy;
    validate(newX, newY, width, height);
    x = newX;
    y = newY;
}

void Rectangle::Resize(double newWidth, double newHeight)
{
    validate(x, y, newWidth, newHeight);
    width = newWidth;
    height = newHeight;
}

void Rectangle::Scale(double factor)
{
    if (!isfinite(factor) || factor <= 0)
        throw invalid_argument("scale factor must be a finite number greater than 0");
    Resize(width * factor, height * factor);
}

double Rectangle::Area() const
{
    return width * height;
}

double Rectangle::Perimeter() const
{
    return 2 * (width + height);
}

bool Rectangle::Intersects(const Rectangle& other) const
{
    return max(x, other.x) < min(getRight(), other.getRight())
        && max(y, other.y) < min(getTop(), other.getTop());
}

Rectangle Rectangle::BoundingRectangle(const Rectangle& other) const
{
    double left = min(x, other.x);
    double bottom = min(y, other.y);
    double right = max(getRight(), other.getRight());
    double top = max(getTop(), other.getTop());
    return Rectangle(left, bottom, right - left, top - bottom);
}

bool Rectangle::Intersection(const Rectangle& other, Rectangle& result) const
{
    double left = max(x, other.x);
    double bottom = max(y, other.y);
    double right = min(getRight(), other.getRight());
    double top = min(getTop(), other.getTop());

    if (right <= left || top <= bottom)
        return false;

    result.Init(left, bottom, right - left, top - bottom);
    return true;
}
