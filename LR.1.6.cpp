#include "FractionC.h"
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

template <typename P>
static void ComparePairs(const P& a, const P& b)
{
    cout << a.toString() << " vs " << b.toString() << endl;
    cout << "   Equal          : " << a.Equal(b) << endl;
    cout << "   NotEqual       : " << a.NotEqual(b) << endl;
    cout << "   Greater        : " << a.Greater(b) << endl;
    cout << "   GreaterOrEqual : " << a.GreaterOrEqual(b) << endl;
    cout << "   Less           : " << a.Less(b) << endl;
    cout << "   LessOrEqual    : " << a.LessOrEqual(b) << endl;
}

static void CompareFractions(const FractionC& a, const FractionC& b)
{
    cout << a.toDouble() << " vs " << b.toDouble() << endl;
    cout << "   Equal          : " << a.Equal(b) << endl;
    cout << "   NotEqual       : " << a.NotEqual(b) << endl;
    cout << "   Greater        : " << a.Greater(b) << endl;
    cout << "   GreaterOrEqual : " << a.GreaterOrEqual(b) << endl;
    cout << "   Less           : " << a.Less(b) << endl;
    cout << "   LessOrEqual    : " << a.LessOrEqual(b) << endl;
}

static FractionC MaxFraction(const FractionC& a, const FractionC& b)
{
    return a.Greater(b) ? a : b;
}

int main()
{
    cout << boolalpha;

    try
    {
        cout << "============ class FractionC (nested Pair) ============" << endl;

        cout << endl << "--- creation ---" << endl;
        FractionC f1;
        FractionC f2(3, 0.25);
        FractionC f3 = f2;
        FractionC f4 = FractionC::FromDouble(-2.25);
        FractionC f5;
        f5.Init(3, 0.5);
        FractionC farr1[2];
        FractionC farr2[3] = { FractionC(1, 0.5), FractionC::FromDouble(7.125), FractionC(-4, 0.0) };
        FractionC* pf = new FractionC(10, 0.9);
        FractionC* pfa = new FractionC[2];
        pfa[0].Init(5, 0.5);
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

        cout << endl << "--- nested class Pair, used through the container ---" << endl;
        auto p = f2.getPair();
        cout << "f2.getPair() = " << p.toString() << endl;
        p.Display();
        p.setSecond(0.75);
        cout << "changed copy   = " << p.toString() << endl;
        cout << "f2 is unchanged = " << f2.toString() << endl;
        f2.setPair(p);
        cout << "after f2.setPair(copy) = " << f2.toString() << endl;
        Attempt("p.setFirst(+inf)      ", [&] { p.setFirst(numeric_limits<double>::infinity()); });
        Attempt("p.setSecond(NaN)      ", [&] { p.setSecond(numeric_limits<double>::quiet_NaN()); });
        Attempt("p.Init(1, +inf)       ", [&] { p.Init(1, numeric_limits<double>::infinity()); });

        cout << endl << "--- getters / setters ---" << endl;
        f1.setWhole(10);
        f1.setFrac(0.125);
        cout << "f1 = " << f1.toString() << ", getWhole() = " << f1.getWhole()
            << ", getFrac() = " << f1.getFrac() << endl;
        auto q = f1.getPair();
        q.setFirst(1000.5);
        cout << "f1 after changing the copy = " << f1.toString() << endl;
        Attempt("f1.setFrac(1.0)       ", [&] { f1.setFrac(1.0); });
        Attempt("f1.setFrac(-0.1)      ", [&] { f1.setFrac(-0.1); });
        Attempt("f1.setPair(1000.5; 0.125)", [&] { f1.setPair(q); });
        Attempt("f1.setWhole(2^60)     ", [&] { f1.setWhole(1LL << 60); });
        Attempt("f1.Init(1, NaN)       ", [&] { f1.Init(1, numeric_limits<double>::quiet_NaN()); });
        cout << "f1 after rejected calls = " << f1.toString() << endl;

        cout << endl << "--- comparison of pairs ---" << endl;
        ComparePairs(f2.getPair(), f5.getPair());
        ComparePairs(f3.getPair(), f3.getPair());

        cout << endl << "--- comparison of fractions ---" << endl;
        CompareFractions(f3, f5);
        CompareFractions(f3, f3);
        CompareFractions(f4, f1);

        FractionC m = MaxFraction(f3, f5);
        cout << "MaxFraction(f3, f5) = " << m.toString() << endl;
        FractionC maxF = farr2[0];
        for (int i = 1; i < 3; i++)
            maxF = MaxFraction(maxF, farr2[i]);
        cout << "largest fraction in farr2 = " << maxF.toString() << endl;

        delete pf;
        delete[] pfa;

        cout << endl << "--- Read from keyboard ---" << endl;
        FractionC f6;
        f6.Read();
        cout << "you entered:" << endl;
        f6.Display();
        cout << "f6 = " << f6.toString() << endl;
        CompareFractions(f6, f3);
    }
    catch (const runtime_error& e)
    {
        cout << endl << "Stopped: " << e.what() << endl;
    }

    return 0;
}
