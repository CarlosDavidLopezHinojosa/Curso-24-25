#ifndef MULTIPLICACIONMATRIZ_HPP
#define MULTIPLICACIONMATRIZ_HPP
#include "common.hpp"

void MultiplicacionMatrices(std::vector<std::vector<double>>& A, 
                            std::vector<std::vector<double>>& B, 
                            std::vector<std::vector<double>>& C);

void tiempoMultiplicacionMatrices(int nMin, int nMax, int repeticiones, 
                       std::vector<double>& tiemposReales, 
                       std::vector<double>& numeroElementos);

void ajusteCubico(const std::vector<double>& numeroElementos, 
                      const std::vector<double>& tiemposReales, 
                      std::vector<double>& a);


#endif