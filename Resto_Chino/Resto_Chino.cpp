#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sstream>
#include <NTL/ZZ.h>
using namespace std;
using namespace NTL;

ZZ modulo(ZZ a, ZZ b)
{
    ZZ r;
    r = a - b * (a / b);
    r = r + (r < 0) * b;
    return r;
}
ZZ euclides (ZZ x, ZZ y)
{
	ZZ q,r;
	q = x/y;
	r = modulo(x,y);

	while (r!=0)
	{
		x = y;
		y = r;
		q = x/y;
		r = modulo(x,y);
	}
	return y;
}
ZZ euclidesext(ZZ a, ZZ b)
{
	ZZ r1,r2,s1,s2,t1,t2,d;
	r1 = a;
	r2 = b;
	s1 = 1;
	s2 = 0;
	t1 = 0;
	t2 = 1;
	d = euclides(a,b);
	ZZ r, s, t;

	while (r2>0)
	{
		ZZ q ;
		q = r1 / r2;
		r = r1 - (q*r2);
		r1 = r2;
		r2 = r;

		s = s1 - (q*s2);
		s1 = s2;
		s2 = s;

		t = t1 - (q*t2);
		t1 = t2;
		t2 = t;
	}
	return s1; //Inversa
}
ZZ inversa(ZZ a, ZZ b)
{
	ZZ inv;
	inv = euclidesext(a, b);
	if (inv < 0)
	{
		inv = modulo(inv, b);
	}
	return inv;
}
ZZ resto (ZZ a1,ZZ n1,ZZ a2,ZZ n2,ZZ a3,ZZ n3)
{
    if (euclides(n1,n2)==1 && euclides(n1,n3)==1 && euclides(n2,n3)==1)
    {
        ZZ N;
        N = n1*n2*n3;

        ZZ div1, div2, div3;
        div1 = N/n1;
        div2 = N/n2;
        div3 = N/n3;

        ZZ y1, y2, y3;
        y1 = inversa(div1,n1);
        y2 = inversa(div2,n2);
        y3 = inversa(div3,n3);

        ZZ x;
        x = (a1*div1*y1)+(a2*div2*y2)+(a3*div3*y3);
        x = modulo(x,N);
        cout<<"El valor de x es: ";
        return x;
    }
    else
    {
        cout<<"Los modulos no son coprimos entre si, por lo que no cumple las condiciones para el uso del teorema."<<endl;
    }
}

int main(){
	ZZ a, b, c, n1, n2, n3;
	a = conv<ZZ>("2");
	b = conv<ZZ>("4");
	c = conv<ZZ>("8");
	n1 = conv<ZZ>("9");
	n2 = conv<ZZ>("10");
	n3 = conv<ZZ>("11");
	cout<<resto(a,n1,b,n2,c,n3);
}
