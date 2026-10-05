
#include "Rectangle.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

using namespace std;

static int readInt(const string& prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
            return value;
        if (cin.eof())
            throw runtime_error("input stream closed");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid integer, try again." << endl;
    }
}

static double readDouble(const string& prompt)
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

static void ShowBoth(const Rectangle& a, const Rectangle& b)
{
    cout << endl;
    cout << "A = " << a.toString() << endl;
    cout << "B = " << b.toString() << endl;
}

static void PrintMenu()
{
    cout << endl;
    cout << "=========================== MENU ===========================" << endl;
    cout << " 1  - read rectangle A from keyboard   (Read)" << endl;
    cout << " 2  - read rectangle B from keyboard   (Read)" << endl;
    cout << " 3  - show A and B                     (Display)" << endl;
    cout << " 4  - show A and B                     (getters + toString)" << endl;
    cout << " 5  - change one field of A            (setters)" << endl;
    cout << " 6  - re-initialize A                  (Init)" << endl;
    cout << " 7  - move A                           (Move)" << endl;
    cout << " 8  - resize A                         (Resize)" << endl;
    cout << " 9  - scale A                          (Scale)" << endl;
    cout << " 10 - area and perimeter of A and B    (Area, Perimeter)" << endl;
    cout << " 11 - smallest rectangle containing A and B (BoundingRectangle)" << endl;
    cout << " 12 - intersection of A and B          (Intersects, Intersection)" << endl;
    cout << " 13 - demo: ways to create objects and arrays of objects" << endl;
    cout << " 0  - exit" << endl;
    cout << "============================================================" << endl;
}

static void DemoCreation()
{
    cout << endl << "--- 1. single objects ---" << endl;
    Rectangle r1;
    Rectangle r2(1, 2, 3, 4);
    Rectangle r3 = r2;
    Rectangle r4(r2);
    Rectangle r5;
    r5.Init(-1, -1, 2, 2);
    cout << "r1 (default)      : " << r1.toString() << endl;
    cout << "r2 (parameters)   : " << r2.toString() << endl;
    cout << "r3 (= r2)         : " << r3.toString() << endl;
    cout << "r4 (copy of r2)   : " << r4.toString() << endl;
    cout << "r5 (Init)         : " << r5.toString() << endl;

    cout << endl << "--- 2. static arrays ---" << endl;
    Rectangle arr1[3];
    for (int i = 0; i < 3; i++)
        arr1[i].Init(i, i, i + 1, i + 1);
    Rectangle arr2[3] = { Rectangle(0, 0, 1, 1),
                          Rectangle(2, 2, 2, 2),
                          Rectangle(-1, 3, 5, 1) };
    for (int i = 0; i < 3; i++)
        cout << "arr1[" << i << "] = " << arr1[i].toString() << endl;
    for (int i = 0; i < 3; i++)
        cout << "arr2[" << i << "] = " << arr2[i].toString() << endl;

    Rectangle all = arr2[0];
    for (int i = 1; i < 3; i++)
        all = all.BoundingRectangle(arr2[i]);
    cout << "bounding rectangle of arr2: " << all.toString() << endl;

    cout << endl << "--- 3. dynamic objects and arrays ---" << endl;
    Rectangle* p = new Rectangle(5, 5, 1, 1);
    int n = 2;
    Rectangle* pa = new Rectangle[n];
    pa[0].Init(0, 0, 10, 10);
    pa[1] = *p;
    cout << "*p    = " << p->toString() << endl;
    for (int i = 0; i < n; i++)
        cout << "pa[" << i << "] = " << pa[i].toString() << endl;
    delete p;
    delete[] pa;
}

int main()
{
    Rectangle a;
    Rectangle b(2, 1, 4, 3);

    try
    {
        int choice;
        do
        {
            PrintMenu();
            choice = readInt("choice = ? ");

            try
            {
                switch (choice)
                {
                case 1:
                    a.Read();
                    a.Display();
                    break;

                case 2:
                    b.Read();
                    b.Display();
                    break;

                case 3:
                    cout << endl << "A:";
                    a.Display();
                    cout << endl << "B:";
                    b.Display();
                    break;

                case 4:
                    cout << endl;
                    cout << "A: x = " << a.getX() << ", y = " << a.getY()
                        << ", width = " << a.getWidth() << ", height = " << a.getHeight()
                        << ", right = " << a.getRight() << ", top = " << a.getTop() << endl;
                    cout << "B: x = " << b.getX() << ", y = " << b.getY()
                        << ", width = " << b.getWidth() << ", height = " << b.getHeight()
                        << ", right = " << b.getRight() << ", top = " << b.getTop() << endl;
                    ShowBoth(a, b);
                    break;

                case 5:
                {
                    cout << "field: 1 - x, 2 - y, 3 - width, 4 - height" << endl;
                    int field = readInt("field = ? ");
                    if (field < 1 || field > 4)
                    {
                        cout << "Unknown field." << endl;
                        break;
                    }
                    double value = readDouble("value = ? ");
                    switch (field)
                    {
                    case 1: a.setX(value); break;
                    case 2: a.setY(value); break;
                    case 3: a.setWidth(value); break;
                    case 4: a.setHeight(value); break;
                    }
                    cout << "A = " << a.toString() << endl;
                    break;
                }

                case 6:
                {
                    double x = readDouble("x      = ? ");
                    double y = readDouble("y      = ? ");
                    double w = readDouble("width  = ? ");
                    double h = readDouble("height = ? ");
                    a.Init(x, y, w, h);
                    cout << "A = " << a.toString() << endl;
                    break;
                }

                case 7:
                {
                    double dx = readDouble("dx = ? ");
                    double dy = readDouble("dy = ? ");
                    a.Move(dx, dy);
                    cout << "A = " << a.toString() << endl;
                    break;
                }

                case 8:
                {
                    double w = readDouble("new width  = ? ");
                    double h = readDouble("new height = ? ");
                    a.Resize(w, h);
                    cout << "A = " << a.toString() << endl;
                    break;
                }

                case 9:
                {
                    double k = readDouble("factor = ? ");
                    a.Scale(k);
                    cout << "A = " << a.toString() << endl;
                    break;
                }

                case 10:
                    cout << endl;
                    cout << "A: area = " << a.Area() << ", perimeter = " << a.Perimeter() << endl;
                    cout << "B: area = " << b.Area() << ", perimeter = " << b.Perimeter() << endl;
                    break;

                case 11:
                {
                    Rectangle c = a.BoundingRectangle(b);
                    ShowBoth(a, b);
                    cout << "Bounding rectangle = " << c.toString() << endl;
                    break;
                }

                case 12:
                {
                    Rectangle c;
                    ShowBoth(a, b);
                    cout << "Intersects: " << (a.Intersects(b) ? "yes" : "no") << endl;
                    if (a.Intersection(b, c))
                        cout << "Intersection = " << c.toString() << endl;
                    else
                        cout << "Rectangles have no common part." << endl;
                    break;
                }

                case 13:
                    DemoCreation();
                    break;

                case 0:
                    cout << "Bye." << endl;
                    break;

                default:
                    cout << "Unknown menu item." << endl;
                }
            }
            catch (const invalid_argument& e)
            {
                cout << "Error: " << e.what() << endl;
            }
        } while (choice != 0);
    }
    catch (const runtime_error& e)
    {
        cout << endl << "Stopped: " << e.what() << endl;
    }

    return 0;
}
