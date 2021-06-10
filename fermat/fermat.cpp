#include <iostream>
#include <vector>
#include <NTL/ZZ.h>
using namespace NTL;

ZZ mimodulo(ZZ x, ZZ y)
{
    ZZ div = x / y;
    ZZ modulo = -(div * y) + x;
    if (modulo < 0)
        modulo += y;
    return modulo;
}

int Contador_Bucles=0;

ZZ mcd(ZZ x, ZZ y)
{
    ZZ modulo;
    while (y != 0)
    {
        Contador_Bucles++;
        modulo = mimodulo(x, y);
        x = y;
        y = modulo;
    }
    return x;
}

ZZ potencia(ZZ x, ZZ y)
{
    ZZ counter; counter = 0;
    ZZ result; result = x;
    if (y == 0) {
        return ZZ(1);
    }
    else if (y == 1) {
        return x;
    }
    while (counter != y - 1) {
        result = result * x;
        counter++;
    }
    return result;
}

ZZ fermat(ZZ x, ZZ y){
    ZZ res;
    if(mcd(x,y)!=1){std::cout<<"\n El mcd de los numeros ingresados no es 1"; return ZZ(0);}
    else{res=mimodulo(potencia(x,(y-1)),y);}
    std::cout<<"Res: "<<x<<" ^ "<<y-1<<" (mod "<<y<<") = "<<res;
    return res;
}

int main()
{
    ZZ a, b;
    a=RandomPrime_ZZ(16); b=RandomPrime_ZZ(16);
    a=13;b=12;
    euler(a,b);
    std::cout<<"\n Bucles: "<<Contador_Bucles;

}
