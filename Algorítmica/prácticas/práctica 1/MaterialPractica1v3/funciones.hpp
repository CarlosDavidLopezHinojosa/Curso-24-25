#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <random>
#include <cmath>
#include <algorithm>
#include "ClaseTiempo.cpp"
#include "sistemaEcuaciones.hpp"

// Definición de las funciones que utilizaremos para todos los ajuste de complejidad
 
void rellenarVector(std::vector<int>& vec);

void rellenarMatriz(std::vector<std::vector<double>>& A);

double sumatorio(std::vector<double>& n, std::vector<double>& t, int expN, int expT);

double calcularTiempoEstimadoPolinomico(const double& n,const std::vector<double>& a);

void calcularTiemposEstimadosPolinomico(const std::vector<double>& numeroElementos, 
                                        const std::vector<double>& a, 
                                        std::vector<double>& tiemposEstimados);

void ajustePolinomicoGeneral(const std::vector<double>& numeroElementos, 
                             const std::vector<double>& tiemposReales, 
                             std::vector<double>& a, 
                             int grado_del_polinomio);

double calcularCoeficienteDeterminacion(const std::vector<double>& tiemposReales, 
                                        const std::vector<double>& tiemposEstimados);

void guardarDatos(std::string nombre_fichero,
                  std::vector<double>& numeroElementos,
                  std::vector<double>& tiemposReales, 
                  std::vector<double>& tiemposEstimados);


//Definición de las funciones para realizar el analisis de complejidad de la Ordenación burbuja O(n^2)

void OrdenacionBurbuja(std::vector<int>& vec);

bool estaOrdenado(const std::vector<int>& vec);

void tiemposOrdenacionBurbuja(int nMin, int nMax, int incremento, int repeticiones, 
                              std::vector<double>& tiemposReales, 
                              std::vector<double>& numeroElementos);

void ajusteCuadratico(const std::vector<double>& numeroElementos, 
                      const std::vector<double>& tiemposReales, 
                      std::vector<double>& a);


// Definición de las funciones para realizar el analisis de complejidad de la Multiplicación de Matrices de orden n O(n^3)

void MultiplicacionMatrices(std::vector<std::vector<double>>& A, 
                            std::vector<std::vector<double>>& B, 
                            std::vector<std::vector<double>>& C);

void tiempoMultiplicacionMatrices(int nMin, int nMax, int repeticiones, 
                                  std::vector<double>& tiemposReales, 
                                  std::vector<double>& numeroElementos);

void ajusteCubico(const std::vector<double>& numeroElementos, 
                  const std::vector<double>& tiemposReales, 
                  std::vector<double>& a);


// Definición de las funciones para realizar el analisis de complejidad del calculo del determinate de manera recursiva O(n!)
 
double DeterminanteRecursivo(const std::vector<std::vector<double>>& m, int n);

void tiempoDeterminanteRecursivo(int nMin, int nMax, int repeticiones, 
                                 std::vector<double>& tiemposReales, 
                                 std::vector<double>& numeroElementos);

double sumatorioFactorial(std::vector<double>& n, std::vector<double>& t, int expN, int expT);

void ajusteFactorial(const std::vector<double>& numeroElementos, 
                     const std::vector<double>& tiemposReales, 
                     std::vector<double>& a);

double  calcularTiempoEstimadoFactorial(const double &n, const std::vector<double>& a);


void calcularTiemposEstimadosFactorial(const std::vector<double>& numeroElementos, 
                                       const std::vector<double>& a, 
                                       std::vector<double>& tiemposEstimados);


#endif