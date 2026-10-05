#pragma once
#include <string>

class Rectangle
{
private:
    double x;
    double y;
    double width;
    double height;

public:
    Rectangle();
    Rectangle(double x, double y, double width, double height);

    double getX() const { return x; }
    double getY() const { return y; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    double getRight() const { return x + width; }
    double getTop() const { return y + height; }

    void setX(double x);
    void setY(double y);
    void setWidth(double width);
    void setHeight(double height);

    void Init(double x, double y, double width, double height);
    void Read();
    void Display() const;
    std::string toString() const;

    void Move(double dx, double dy);
    void Resize(double newWidth, double newHeight);
    void Scale(double factor);
    double Area() const;
    double Perimeter() const;

    bool Intersects(const Rectangle& other) const;
    Rectangle BoundingRectangle(const Rectangle& other) const;
    bool Intersection(const Rectangle& other, Rectangle& result) const;
};
