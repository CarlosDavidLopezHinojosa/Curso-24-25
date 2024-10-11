#include <string>
#include <cstdio>	//Funciones de cadenas
#include <cstdlib>
#include <cctype>
#include <iostream>

#include "entero.hpp"

#include <cmath>
  
using namespace std;
void Entero::partirEntero(Entero  &e1, Entero &e2) const
{
	int n;
	int n1, n2;
	int i;
	
	n = size();
	
	if (n % 2 == 0) //n es par
	{
		n1 = n / 2;
		n2 = n1;
	}
	else
	{
		n1 = (n + 1) / 2;
		n2 = n1 - 1;
	}
	
	//Extrae la primera mitad del número y lo asigna al Entero c1
	e1.setString(getString().substr(0,n1));

	//Extrae la segunda mitad del número y lo asigna al Entero c2
	e2.setString(getString().substr(n1,n));	
}

void Entero::agregarCerosDelante(int nCeros)	
{
	for (int i = 0; i < nCeros; ++i)
		setString('0'+getString());
}

void Entero::quitarCerosNoSignificativos()
{
	int  tam;
	bool continuar=true;
	string strNum = getString();

	while(continuar==true)
	{
		tam=strNum.length();

		if (strNum[0]=='0')
			strNum = strNum.substr(1,tam);
		else
			continuar = false;
	}
	setString(strNum);
}

Entero & Entero::multiplicarPotencia10(int potencia) const
{
	Entero e;

	e = *this;

	for (int i = 0; i < potencia; i++)
		e.setString(e.getString() + '0');

	return *(new Entero(e));
}




Entero & Entero::operator+(const Entero &e) const
{  
	//objeto de la clase donde guardaremos el resultado para poder devolverlo	
	Entero aux;

	//Creamos dos enteros locales para guardar los sumandos
	Entero e1 = *this;
    Entero e2 = e;

	//String donde guardaremos el resultado
	string resultado;

	//Para guardar la suma de cada elemento de los string
	int suma;

	//guardar tamaño entero
	int maxSize;

	//Comprobamos el tamaño de la cadena para ver si hay que añadirle 0
	if (e2.size() > e1.size())
	{	//Hay que añadirle 0 entero que invoca, tantos como haya de diferencia de tamaños entre las 2
		e1.agregarCerosDelante(e2.size() - e1.size());
		maxSize = e2.size();
	}
	else if(e2.size() < e1.size())
	{
		e2.agregarCerosDelante(e1.size() - e2.size());
		maxSize = e1.size();
	}
	else
		maxSize = e1.size();

	//Extraemos los strings y los sumamos  caracter por caracter
	string c1, c2;

	c1 = e1.getString();
	c2 = e2.getString();

	//Inicializamos acarreo a 0
	int acarreo = 0;

	for (int i = maxSize - 1; i >= 0; --i)
	{	
		//Suma de caracteres pasados a integer
		suma = (c1[i] - '0') + (c2[i] - '0') + acarreo;		
		
		// Actualizamos el acarreo y añadimos el resultado a la cadena
		acarreo = suma / 10;
		suma = suma % 10;

		//Inserta en la posición 0, 1 caracter que es suma + '0'
		resultado.insert(0, 1, suma + '0');
	}

	// Añadimos el acarreo final
	if (acarreo == 1)
		resultado.insert(0, 1, acarreo + '0');

	//Creamos un entero a partir del string resultado y lo devolvemos
	//Se devuelve el contenido del puntero creado con new
	//aux.quitarCerosNoSignificativos();
	
	return *(new Entero(resultado)); 
}


Entero& Entero::operator*(const Entero &e) const
{ 
	//Implementar
	Entero u = *this;
	Entero v = e;
	Entero N;
	int max = this->maxTam();

	if (u <= v)
	{
		N = v;
		u.agregarCerosDelante(v.size() - u.size());
	}
	else
	{
		N = u;
		v.agregarCerosDelante(u.size() - v.size());
	}
	
	if (N.size() <= max)
	{
		int a = stoll(u.getString());
		int b = stoll(v.getString());

		return *(new Entero(a * b));
	}
	else
	{
		int s = N.size() / 2;
		Entero W,X,Y,Z;
		u.partirEntero(W,X);
		v.partirEntero(Y,Z);

		Entero R = (W + X) * (Y + Z);
		Entero P = (W * Y);
		Entero Q = (X * Z);

		Entero M = P.multiplicarPotencia10(2*s) + (R - P - Q).multiplicarPotencia10(s) + Q;
		M.quitarCerosNoSignificativos();
		return *(new Entero(M));
	}
}



Entero & Entero::factorial() const
{
	//Implementar
	Entero uno("1");
	Entero inc("1");
	Entero result("1");

	while (inc <= *this)
	{
		result = result * inc;
		inc = inc + uno;
	}

	return *(new Entero(result));
	
}

bool Entero::operator<=(const Entero &e) const
{
	//Implementar
	Entero e1 = *this;
	Entero e2 = e;

	e1.quitarCerosNoSignificativos();
	e2.quitarCerosNoSignificativos();

	return ((e1.size() == e2.size()) ? e1.getString() <= e2.getString() : e1.size() <= e2.size());
	
}

bool Entero::operator==(const Entero &e) const
{
	//Implementar
	return this->getString() == e.getString();
}

//Sobrecarga del operador de entrada
istream &operator>>(istream &stream, Entero &a) 
{
		
	string x;
	stream>>x;
	a.setString(x);

	// Se devuelve el flujo de entrada
	return stream;
}


//Sobrecarga del operador de salida
ostream &operator<<(ostream &stream, Entero &a) 
{
	stream<<a.getString();

	// Se devuelve el flujo de salida
	return stream;
}