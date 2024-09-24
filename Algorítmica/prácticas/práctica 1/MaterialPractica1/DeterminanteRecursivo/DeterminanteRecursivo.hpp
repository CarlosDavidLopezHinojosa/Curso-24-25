#ifndef DETERMINANTERECURSIVO_HPP
#define DETERMINANTERECURSIVO_HPP
#include "common.hpp"

double DeterminanteRecursivo(const std::vector<std::vector<double>>& m, int n);

void tiempoDeterminanteRecursivo(int nMin, int nMax, int repeticiones, 
                       std::vector<double>& tiemposReales, 
                       std::vector<double>& numeroElementos);

void ajusteFactorial(const std::vector<double>& numeroElementos, 
                      const std::vector<double>& tiemposReales, 
                      std::vector<double>& a);

double  calcularTiempoEstimadoFactorial(const double &n, const std::vector<double>& a);


void calcularTiemposEstimadosFactorial(const std::vector<double>& numeroElementos, 
                      const std::vector<double>& a, 
                      std::vector<double>& tiemposEstimados);
#endif