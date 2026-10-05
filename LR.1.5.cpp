#include "Fraction.h"
#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

using namespace std;

static void Attempt(const string& what, const function<void()>& action)
{
    try
    {
        action();
        cout << what << ": accepted" << endl;
    }
    catch (const invalid_argument& e)
    {
        cout << what << ": rejected (" << e.what() << ")" << endl;
    }
}

static void ComparePairs(const Pair& a, const Pair& b)
{
    cout << a.toString() << " vs " << b.toString() << endl;
    cout << "   Equal          : " << a.Equal(b) << endl;
    cout << "   NotEqual       : " << a.NotEqual(b) << endl;
    cout << "   Greater        : " << a.Greater(b) << endl;
    cout << "   GreaterOrEqual : " << a.GreaterOrEqual(b) << endl;
    cout << "   Less           : " << a.Less(b) << endl;
    cout << "   LessOrEqual    : " << a.LessOrEqual(b) << endl;
}

static void CompareFractions(const Fraction& a, const Fraction& b)
{
    cout << a.toDouble() << " vs " << b.toDouble() << endl;
    cout << "   Equal          : " << a.Equal(b) << endl;
    cout << "   NotEqual       : " << a.NotEqual(b) << endl;
    cout << "   Greater        : " << a.Greater(b) << endl;
    cout << "   GreaterOrEqual : " << a.GreaterOrEqual(b) << endl;
    cout << "   Less           : " << a.Less(b) << endl;
    cout << "   LessOrEqual    : " << a.LessOrEqual(b) << endl;
}

static Fraction MaxFraction(const Fraction& a, const Fraction& b)
{
    return a.Greater(b) ? a : b;
}

int main()
{
    cout << boolalpha;

    try
    {
        cout << "================ class Pair ================" << endl;

        cout << endl << "--- creation ---" << endl;
        Pair p1;
        Pair p2(2, 0.5);
        Pair p3 = p2;
        Pair p4;
        p4.Init(2, 0.75);
        Pair parr1[3];
        Pair parr2[3] = { Pair(1, 1), Pair(3, 0.5), Pair(3, 0.25) };
        Pair* pp = new Pair(7, 7);
        Pair* pdyn = new Pair[2];
        pdyn[0].Init(-1, 5);
        pdyn[1] = *pp;

        cout << "p1 = " << p1.toString() << endl;
        cout << "p2 = " << p2.toString() << endl;
        cout << "p3 = " << p3.toString() << endl;
        cout << "p4 = " << p4.toString() << endl;
        p4.Display();
        for (int i = 0; i < 3; i++)
            cout << "parr1[" << i << "] = " << parr1[i].toString() << endl;
        for (int i = 0; i < 3; i++)
            cout << "parr2[" << i << "] = " << parr2[i].toString() << endl;
        for (int i = 0; i < 2; i++)
            cout << "pdyn[" << i << "] = " << pdyn[i].toString() << endl;

        cout << endl << "--- getters / setters ---" << endl;
        p1.setFirst(10);
        p1.setSecond(-2.5);
        cout << "p1 = " << p1.toString() << ", getFirst() = " << p1.getFirst()
            << ", getSecond() = " << p1.getSecond() << endl;
        Attempt("p1.setFirst(+inf)", [&] { p1.setFirst(numeric_limits<double>::infinity()); });
        Attempt("p1.setSecond(NaN)", [&] { p1.setSecond(numeric_limits<double>::quiet_NaN()); });
        Attempt("p1.Init(1, +inf)  ", [&] { p1.Init(1, numeric_limits<double>::infinity()); });
        cout << "p1 after rejected calls = " << p1.toString() << endl;

        cout << endl << "--- comparison ---" << endl;
        ComparePairs(p2, p4);
        ComparePairs(p2, p3);
        ComparePairs(p1, p2);

        Pair maxPair = parr2[0];
        for (int i = 1; i < 3; i++)
            if (parr2[i].Greater(maxPair))
                maxPair = parr2[i];
        cout << "largest pair in parr2: " << maxPair.toString() << endl;

        delete pp;
        delete[] pdyn;

        cout << endl << "============== class Fraction ==============" << endl;

        cout << endl << "--- creation ---" << endl;
        Fraction f1;
        Fraction f2(3, 0.25);
        Fraction f3 = f2;
        Fraction f4 = Fraction::FromDouble(-2.25);
        Fraction f5;
        f5.Init(3, 0.5);
        Fraction farr1[2];
        Fraction farr2[3] = { Fraction(1, 0.5), Fraction::FromDouble(7.125), Fraction(-4, 0.0) };
        Fraction* pf = new Fraction(10, 0.9);
        Fraction* pfa = new Fraction[2];
        pfa[0].setPair(Pair(5, 0.5));
        pfa[1] = *pf;

        cout << "f1 = " << f1.toString() << endl;
        cout << "f2 = " << f2.toString() << endl;
        cout << "f3 = " << f3.toString() << endl;
        cout << "f4 = " << f4.toString() << endl;
        cout << "f5 = " << f5.toString() << endl;
        f2.Display();
        for (int i = 0; i < 2; i++)
            cout << "farr1[" << i << "] = " << farr1[i].toString() << endl;
        for (int i = 0; i < 3; i++)
            cout << "farr2[" << i << "] = " << farr2[i].toString() << endl;
        for (int i = 0; i < 2; i++)
            cout << "pfa[" << i << "] = " << pfa[i].toString() << endl;

        cout << endl << "--- getters / setters ---" << endl;
        f1.setWhole(10);
        f1.setFrac(0.125);
        cout << "f1 = " << f1.toString() << ", getWhole() = " << f1.getWhole()
            << ", getFrac() = " << f1.getFrac() << endl;
        f1.setPair(Pair(4, 0.5));
        Pair inner = f1.getPair();
        inner.setFirst(1000.5);
        cout << "f1 after changing the copy = " << f1.toString() << endl;
        Attempt("f1.setFrac(1.0)       ", [&] { f1.setFrac(1.0); });
        Attempt("f1.setFrac(-0.1)      ", [&] { f1.setFrac(-0.1); });
        Attempt("f1.setPair((1.5, 0.2))", [&] { f1.setPair(Pair(1.5, 0.2)); });
        Attempt("f1.setPair((1, 3))    ", [&] { f1.setPair(Pair(1, 3)); });
        Attempt("f1.setWhole(2^60)     ", [&] { f1.setWhole(1LL << 60); });
        Attempt("f1.Init(1, NaN)       ", [&] { f1.Init(1, numeric_limits<double>::quiet_NaN()); });
        cout << "f1 after rejected calls = " << f1.toString() << endl;

        cout << endl << "--- comparison ---" << endl;
        CompareFractions(f2, f5);
        CompareFractions(f2, f3);
        CompareFractions(f4, f1);

        Fraction m = MaxFraction(f2, f5);
        cout << "MaxFraction(f2, f5) = " << m.toString() << endl;
        Fraction maxF = farr2[0];
        for (int i = 1; i < 3; i++)
            maxF = MaxFraction(maxF, farr2[i]);
        cout << "largest fraction in farr2 = " << maxF.toString() << endl;

        delete pf;
        delete[] pfa;

        cout << endl << "--- Read from keyboard ---" << endl;
        Fraction f6;
        f6.Read();
        cout << "you entered:" << endl;
        f6.Display();
        cout << "f6 = " << f6.toString() << endl;
        CompareFractions(f6, f2);
    }
    catch (const runtime_error& e)
    {
        cout << endl << "Stopped: " << e.what() << endl;
    }

    return 0;
}
