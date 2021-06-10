#include <iostream>
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

ZZ potenciacionbinariamodular(ZZ x, long long y, ZZ m) {
    ZZ respuesta; respuesta = 1;
    int Contador_bucles=0;
    x = mimodulo(x, m);
    while (y > 0) {
        Contador_bucles++;
        if (y&1) { respuesta = mimodulo(respuesta * x,m); }
        x = mimodulo(x * x,m);
        y >>= 1;
    }
    //COUT DEL BUCLE Y LA RESPUESTA AQUI '-'
    std::cout<<"\n Cantidad de bucles: "<<Contador_bucles;
    std::cout<<"\n respuesta: "<<respuesta;
    return respuesta;
}

int main()
{
    ZZ a,m; a = 572; m = 713;
    long long b=29;
    potenciacionbinariamodular(a,b,m);
}
