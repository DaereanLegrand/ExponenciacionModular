#include <iostream>
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

ZZ moduloZZ2(ZZ a)
{
    ZZ r = a - ((a >> 1) << 1);
    r = r + ((r < 0) << 1);
    return r;
}

ZZ rtlexponentiation(ZZ b, ZZ e, ZZ m)
{
    ZZ A = conv<ZZ>("1");
    ZZ S = b;

    while (e != 0)
    {
        if (moduloZZ2(e) == 1)
        {
            A = moduloZZ(A * S, m);        
        }
        e = e >> 1;
        if (e != 0) S = S * S;
    }
    return A;
}

int main()
{
    ZZ a = conv<ZZ>("2"), b = conv<ZZ>("3"), m = conv<ZZ>("5");
    cout << "Ingrese la base: ";
    cin >> a;
    cout << "Ingrese el exponente: ";
    cin >> b;
    cout << "Ingrese el modulo: ";
    cin >> m;
    ZZ res = rtlexponentiation(a, b, m);
    cout << res << endl;
    return 0;
}
