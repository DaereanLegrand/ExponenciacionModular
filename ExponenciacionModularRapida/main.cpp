#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

ZZ moduloZZ(ZZ a, ZZ b)
{
    ZZ r;
    r = a - b * (a / b);
    r = r + (r < 0) * b;
    return r;
}

ZZ powerZZextra(ZZ a, ZZ b)
{
    ZZ temp = a;
    while (b > 1)
    {
        a = a * temp;
        b--;
    }
    return a;
}

ZZ powerZZ(ZZ a, ZZ b, ZZ N)
{
    ZZ cumulativeExponent, newB, nMod, lastSquare, lastExponent, otherSquare, two;
    cumulativeExponent = 1;
    newB = b;
    lastSquare = a;
    lastExponent = 0;
    otherSquare = 1;
    two = 2;
    do
    {
        nMod = moduloZZ(newB, two);
        if (cumulativeExponent != 1) lastSquare = moduloZZ(powerZZextra(lastSquare, two), N);
        if (nMod == 1)
        {
            lastExponent = lastExponent + cumulativeExponent;
            otherSquare = moduloZZ(lastSquare * otherSquare, N);
        }
        newB = newB / 2;
        cumulativeExponent = cumulativeExponent * 2;
    }
    while (newB > 0);
    return otherSquare;
}

int main()
{
    ZZ a = conv<ZZ>("123");
    ZZ b = conv<ZZ>("456");
    ZZ m = conv<ZZ>("42");
    cout << powerZZ(a, b, m) << endl;
}
