#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <cassert>
#include <cmath>
#include "MultiplicacionMatriz.hpp" // Incluye las funciones de multiplicación de matrices

int main() {
    // Parámetros de prueba
    int nMin = 10;   // Tamaño mínimo de la matriz
    int nMax = 100;  // Tamaño máximo de la matriz
    int repeticiones = 100; // Número de pruebas a realizar

    // Vectores para almacenar los resultados
    std::vector<double> tiemposReales;
    std::vector<double> numeroElementos;

    // Realiza pruebas con la multiplicación de matrices y mide los tiempos
    tiempoMultiplicacionMatrices(nMin, nMax, repeticiones, tiemposReales, numeroElementos);

    // Imprime los tiempos de multiplicación y el número de elementos
    std::cout << "Tiempos Reales de Multiplicación de Matrices (ms):\n";
    for (size_t i = 0; i < tiemposReales.size(); i++) {
        std::cout << "Tamaño: " << static_cast<int>(numeroElementos[i]) << " x " 
                  << static_cast<int>(numeroElementos[i]) << ", Tiempo: " 
                  << tiemposReales[i] << " ms\n";
    }

    // Ajuste cúbico
    std::vector<double> coeficientes(4);  // a0, a1, a2, a3 para el ajuste cúbico
    ajusteCubico(numeroElementos, tiemposReales, coeficientes);

    std::cout << "\nCoeficientes del ajuste cúbico:\n";
    std::cout << "a0: " << coeficientes[0] << ", a1: " << coeficientes[1] 
              << ", a2: " << coeficientes[2] << ", a3: " << coeficientes[3] << "\n";

    // Calcular tiempos estimados a partir del ajuste cúbico
    std::vector<double> tiemposEstimados;
    calcularTiemposEstimadosPolinomico(numeroElementos, coeficientes, tiemposEstimados);

    // Imprimir tiempos estimados
    std::cout << "\nTiempos estimados (ms):\n";
    for (size_t i = 0; i < tiemposEstimados.size(); i++) {
        std::cout << "Tamaño: " << static_cast<int>(numeroElementos[i]) << " x " 
                  << static_cast<int>(numeroElementos[i]) << ", Tiempo estimado: " 
                  << tiemposEstimados[i] << " ms\n";
    }

    // Calcular el coeficiente de determinación R^2
    double R2 = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);
    std::cout << "\nCoeficiente de determinación R^2: " << R2 << "\n";


    std::ofstream file ("mmults.txt");

    assert(file.is_open());

    for (size_t i = 0; i < 10000; i++)
    {
        file << i << " " <<calcularTiempoEstimadoPolinomico(i,coeficientes) << "\n";
    }
    return 0;
}
