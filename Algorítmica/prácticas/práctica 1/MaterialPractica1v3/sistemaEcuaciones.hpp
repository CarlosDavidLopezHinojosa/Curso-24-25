#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <iostream>
#include <vector> //para manejar la clase vector de la STL>
#include <cmath>
#include <cstdlib>

using namespace std;

void inicializarInversa(vector < vector < double > >  &inversa);
void trianguloInferior(vector < vector < double > > &A, vector < vector < double > > &inversa);
bool  eliminarCero(vector < vector < double > > &A, vector < vector < double > > &inversa, unsigned int x);
void hacerCerosColumna(vector < vector < double > > &A, vector < vector < double > > &inversa, unsigned int x);
void combinarFilas(vector < vector < double > > &matriz, unsigned int filaOrigen, double factor, unsigned int filaDestino);
double productoDiagonal(const vector < vector < double > > &matriz);
void trianguloSuperior(vector < vector < double > > &A, vector < vector < double > > &inversa);
int eliminarCero2(vector < vector < double > > &A, vector < vector < double > > &inversa, unsigned int x);
void hacerCerosColumna2(vector < vector < double > > &A, vector < vector < double > > &inversa, unsigned int x);
void obtenerUnidad(vector < vector < double > > &A, vector < vector < double > > &inversa);
void multiplicarMatrices(const vector < vector < double > > &m1, const vector < vector < double > > &m2, vector < vector < double > > &producto);
void resolverSistemaEcuaciones(vector < vector < double > > A, vector < vector < double > > B, int n, vector < vector < double > > &X);

//A es la matriz de coeficientes de NXN
//B es la matriz de terminos independientes de NX1
//n es el orden de las matrices
//X es el valor de las variables que se obtienen resolviendo el sistema
//Declaracion y reserva de matrices usando el tipo vector de la STL
// vector < vector < double > > matrizDatos;
// matrizDatos = vector< vector< double > >(filas, vector< double >(columnas)); //Matriz de N x N




#endif
