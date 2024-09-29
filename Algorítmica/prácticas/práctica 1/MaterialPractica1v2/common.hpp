#ifndef COMMON_HPP
#define COMMON_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <valarray>
#include <random>
#include <cmath>
#include <algorithm>
#include "ClaseTiempo.hpp"
#include "sistemaEcuaciones.hpp"

void rellenarVector(std::vector<int>& vec);

double sumatorio(std::vector<double>& n, std::vector<double>& t, int expN, int expT);

double calcularTiempoEstimadoPolinomico(const double& n,const std::vector<double>& a);

void calcularTiemposEstimadosPolinomico(const std::vector<double>& numeroElementos, 
                      const std::vector<double>& a, 
                      std::vector<double>& tiemposEstimados);

void ajustePolinomicoGeneral(const std::vector<double>& numeroElementos, 
                      const std::vector<double>& tiemposReales, 
                      std::vector<double>& a, int grado_del_polinomio);

double calcularCoeficienteDeterminacion(const std::vector<double>& tiemposReales, 
                      const std::vector<double>& tiemposEstimados);
                    
void rellenarMatriz(std::vector<std::vector<double>>& A);
#endif