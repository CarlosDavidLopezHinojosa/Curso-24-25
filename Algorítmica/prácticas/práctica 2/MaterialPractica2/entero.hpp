//enteros.h

#ifndef ENTERO_H
#define ENTERO_H

#include <string>
#include <iostream>
using namespace std; 

class Entero
{
	private:
		//Tamaño máximo para que se puedan multiplicar popr hardware
		int tamanoMaximo_; 

		//String donde se guardará el entero como string
		string num_; 

		//Funciones privadas

		//Parte un entero en dos mitades iguales
		void partirEntero(Entero  &e1, Entero &e2) const ;

		//Agrega ceros delante de un entero para igualar su longitud con otro
		void agregarCerosDelante(int nCeros);

		//Elimina ceros no significativos que puede haber en un entero
		void quitarCerosNoSignificativos();

		//Multiplica un entero por una potencia de 10.
		Entero & multiplicarPotencia10(int potencia) const;
		
	public:
		//Contructor
		
		//Este constructor hace que todos los enteros tengan un tamaño máximo de 4 para ser multiplicados
		Entero()
		{	
			tamanoMaximo_= 4;	
		}

		//Constructor a partir de string
		Entero(string str)
		{
			//Implementar
			tamanoMaximo_ = 4;
			num_ = str;
		}

		//Constructor a partir de entero
		Entero(int n)
		{
			//Implementar
			tamanoMaximo_ = 4;
			num_ = to_string(n);
		}

		//Constructor de copia
		Entero(const Entero &e)
		{
			//Implementar
			*this = e;
		}

		//Observador y modificador del atributo privad string
		inline string getString() const
		{
			return num_;
		}
		inline void setString(string x)
		{
			num_ = x;
		}

		//Observador del tamaño del entero
		inline int size() const
		{
			return num_.length();
		}

		//Implementado por mi
		int maxTam() const;
		Entero & operator-(const Entero &e) const;
		
		//Operadores 
		Entero & operator+(const Entero &e) const;
		Entero & operator*(const Entero &e) const;
		bool operator<=(const Entero &e) const;
		bool operator==(const Entero &e) const;
		Entero & factorial() const;
		 
		//Sobrecarga de operadores de entrada y salida
		friend istream &operator>>(istream &stream,Entero &a);
		friend ostream &operator<<(ostream &stream, Entero &a);	
		
};

#endif 