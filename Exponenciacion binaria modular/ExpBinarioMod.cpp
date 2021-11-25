#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <NTL/ZZ.h>


using namespace std;
using namespace NTL;

class rsa {
	//claves privadas para dificultar el acceso a las mismas
		ZZ p;
		ZZ q;
		ZZ phi;
		ZZ d;

	public:
		//valores publicos necesarios para el funcionamiento del algoritmo
		ZZ n;
		ZZ e;
    	rsa(){
    	    //p=RandomPrime_ZZ(16)
    	    //q=RandomPrime_ZZ(16);
        	p=conv<ZZ>("3");
        	q=conv<ZZ>("11");
        	n=p*q;
        	phi=(p-1)*(q-1);
        	e=RandomBnd(n);
        	ZZ aux=e;
        	ZZ mcd=Euclides(phi,aux);
        	do{
        		e=RandomBnd(n);
        		aux=e;
        		mcd=Euclides(phi,aux);
			}while(mcd!=1 || e<2);
			aux=e;
			cout<<"e es: "<<e<<endl;
			vector<ZZ>ext=extMcd(aux,phi);
			//d=EuclidesEx(aux,phi);
			d=ext.at(1);
			cout<<d<<endl;
			if(d<0){
				d=modulo(d,phi);
			}
			cout<<"d es: "<<d;
    	}
    	rsa(ZZ f,ZZ g){
		}
	//funcion para ingresar al valor de a ya que es privado
    ZZ gete(){
        return e;
    }
    //funcion para ingresar al valor de b ya que es privado
    ZZ getn(){
        return n;
    }
    //funcion para ingresar al valor de d ya que es privado
    ZZ getd(){
    	return d;
	}
    // funcion modulo
    ZZ modulo(ZZ a, ZZ b){
    ZZ r;
    r = a - b * (a / b);
    r = r + (r < 0) * b;
    return r;
    }
	//algoritmo base
	ZZ Euclides(ZZ x,ZZ y){
    	ZZ aux=x-((x/y*y));
    	while (aux!= 0){
       		x=y;
       		y=aux;
       		aux= x-((x/y)*y);
    	}
    	return y;
	}
	//algoritmo extendido
	vector<ZZ> extMcd(ZZ a, ZZ b){
    vector<ZZ> temp;
    ZZ q = a / b;
    ZZ res = a - (q * b);

    ZZ s1;
    s1 = 1;
    ZZ s2;
    s2 = 0;
    ZZ s = s1 - (q * s2);

    ZZ t1;
    t1 = 0;
    ZZ t2;
    t2 = 1;
    ZZ t = t1 - (q * t2);

    while (res > 0)
    {
        a = b;
        b = res;
        q = a / b;
        res = a - (q * b);

        s1 = s2;
        s2 = s;
        s = s1 - (q * s2);

        t1 = t2;
        t2 = t;
        t = t1 - (q * t2);

    }
    temp.push_back(b);
    temp.push_back(s2);
    temp.push_back(t2);

    return temp;
    }
    ZZ potenciacionbinariamodular(ZZ x, ZZ y, ZZ m) {
        ZZ respuesta; respuesta = 1;
        x = modulo(x, m);
        while (y > 0) {
            if (modulo(y,ZZ(2))==1) { respuesta = modulo(respuesta * x,m); }
            x = modulo(x * x,m);
            y = y>>1;
        }
        return respuesta;
    }
	//encriptar usando .find para sacar el valor necesario y multiplicar clave a y sumar clave b, pasando respectivamente por modulo para comprobar que sean positivos
    ZZ encriptar(ZZ base,ZZ n,ZZ e){
    	ZZ crp=potenciacionbinariamodular(base,e,n);
    	return crp;
    }
	//descifrar usando .find, consiguiendo el valor necesario para restarle b y multiplicarlo por la inversa de a, pasando por funcion modulo resectivamente
	ZZ descifrar(ZZ base,ZZ n,ZZ d){
    	ZZ drp=potenciacionbinariamodular(base,d,n);
    	return drp;
	}
};
int main(){
	rsa receptor;
  	rsa emisor(receptor.gete(),receptor.getn());
  	ZZ msg=conv<ZZ>("30");
  	ZZ crp=emisor.encriptar(msg,receptor.getn(),receptor.gete());
  	ZZ orgnl=emisor.encriptar(crp,receptor.getn(),receptor.getd());
  	cout<<endl<<"Encriptado: "<<crp<<endl;
  	cout<<endl<<"Descifrado: "<<orgnl;

}
