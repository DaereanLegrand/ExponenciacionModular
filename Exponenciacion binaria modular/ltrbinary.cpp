#include <iostream>
#include <sstream>
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

int moduloZZ2(ZZ a)
{
    ZZ r = a - ((a >> 1) << 1);
    r = r + ((r < 0) << 1);
    if (r == 1) return 1;
    else return 0;
}

string zToString(ZZ z) {
    stringstream buffer;
    buffer << z;
    return buffer.str();
}

string toBinary(ZZ a)
{
    string res;
    while (a != 0)
    {
        if (moduloZZ2(a) == 1) res.insert(0, "1");
        else res.insert(0, "0");
        a = a >> 1;
    }
    return res;        
}

ZZ ltrbinary(ZZ b, ZZ e, ZZ m)
{
    ZZ A(1);
    string exponentBinary = toBinary(e);
    for (string::iterator i = exponentBinary.end() - 1; i != exponentBinary.begin() - 1; i--)
    {
        cout << "*i: " << *i << "\tA: " << A << endl;
        A = moduloZZ(A * A, m);
        if (*i == '1') A = moduloZZ(A * b, m);
    }
    return A;
}

int main()
{
    ZZ b(4), e(7), m(5);
    cout << toBinary(e) << endl;
    cout << ltrbinary(b, e, m) << endl;
}
