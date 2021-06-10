#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
using namespace NTL;

//http://koclab.cs.ucsb.edu/teaching/ecc/eccPapers/Doche-ch09.pdf
ZZ moduloZZ(ZZ a, ZZ b)
{
    ZZ r;
    r = a - b * (a / b);
    r = r + (r < 0) * b;
    return r;
}

string zToString(ZZ z) {
    stringstream buffer;
    buffer << z;
    return buffer.str();
}

string toBase(ZZ a, ZZ b)
{
    string res;
    while (a != 0)
    {
        res.insert(0, zToString(moduloZZ(a, b)));
        a = a / b;
    }
    return res;        
}

ZZ ltrKAry(ZZ b, ZZ e, ZZ t)
{
    vector<ZZ> baseComputation;
    baseComputation.push_back(ZZ(1));
    for (int cont(1); cont < e - 1; cont++)
    {
        baseComputation.push_back(baseComputation.at(cont - 1) * b);
    }
    //cout << baseComputation.size() << endl;
    ZZ A(1);
    string inBase = toBase(e, t);
    //cout << inBase << endl;
    for (int i = inBase.length(); i > 0; i--)
    {
        for (int j = 0; j < b; i++)
        {
            ZZ tempA(1);
            tempA = tempA * A;
        }
        A = A * baseComputation.at(i);
        //cout << i << endl;
    }
    return A;
}

int main()
{
    ZZ a(2), b(8);
    //cout << ltrKAry(a, b, ZZ(4)) << endl;
}
