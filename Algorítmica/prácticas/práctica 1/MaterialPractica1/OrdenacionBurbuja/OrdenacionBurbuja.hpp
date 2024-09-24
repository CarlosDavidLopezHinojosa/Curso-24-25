#ifndef ORDENACIONBURBUJA_HPP
#define ORDENACIONBURBUJA_HPP

#include "common.hpp"


void OrdenacionBurbuja(std::vector<int>& vec);
bool estaOrdenado(const std::vector<int>& vec);

void tiemposOrdenacionBurbuja(int nMin, int nMax, int repeticiones, 
                       std::vector<double>& tiemposReales, 
                       std::vector<double>& numeroElementos);

void ajusteCuadratico(const std::vector<double>& numeroElementos, 
                      const std::vector<double>& tiemposReales, 
                      std::vector<double>& a);
#endif