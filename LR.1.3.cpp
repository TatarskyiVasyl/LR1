#ifdef _WIN32
#define _HAS_STD_BYTE 0
#include <Windows.h>
#endif

#include "Vector3D.h"
#include <iostream>
using namespace std;

int main()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    Vector3D v1;
    v1.Init(1.0, 2.0, 3.0);

    Vector3D v2;
    v2.Read();

    const int N = 3;
    Vector3D arr[N];
    for (int i = 0; i < N; i++)
        arr[i].Init(i + 1.0, i + 2.0, i + 3.0);

    cout << "=== Вектор v1 ===";
    v1.Display();

    cout << endl << "=== Вектор v2 ===";
    v2.Display();

    cout << endl << "=== Масив векторів ===" << endl;
    for (int i = 0; i < N; i++)
        cout << arr[i].toString() << endl;

    Vector3D sum = Vector3D::Add(v1, v2);
    Vector3D diff = Vector3D::Subtract(v1, v2);
    double   dot = Vector3D::Dot(v1, v2);

    cout << endl << "v1 + v2 = " << sum.toString() << endl;
    cout << "v1 - v2 = " << diff.toString() << endl;
    cout << "v1 . v2 = " << dot << endl;

    return 0;
}