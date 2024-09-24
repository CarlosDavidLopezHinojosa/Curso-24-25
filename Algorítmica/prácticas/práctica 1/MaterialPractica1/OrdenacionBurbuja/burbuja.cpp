#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <cassert>
#include <cmath>
#include "OrdenacionBurbuja.hpp" // Incluye las funciones descritas

int main() {
    // Parámetros de prueba
    int nMin = 100;  // Tamaño mínimo del vector
    int nMax = 1000; // Tamaño máximo del vector
    int repeticiones = 1000; // Número de pruebas a realizar

    // Vectores para almacenar los resultados
    std::vector<double> tiemposReales;
    std::vector<double> numeroElementos;

    // Realiza pruebas con ordenación burbuja y mide los tiempos
    tiemposOrdenacionBurbuja(nMin, nMax, repeticiones, tiemposReales, numeroElementos);

    // Imprime los tiempos de ordenación y el número de elementos
    std::cout << "Tiempos Reales de Ordenación (ms):\n";
    for (size_t i = 0; i < tiemposReales.size(); i++) {
        std::cout << "Tamaño: " << numeroElementos[i] << ", Tiempo: " << tiemposReales[i] << " ms\n";
    }

    // Ajuste cuadrático
    std::vector<double> coeficientes(3);  // a0, a1, a2 para el ajuste cuadrático
    ajusteCuadratico(numeroElementos, tiemposReales, coeficientes);

    std::cout << "\nCoeficientes del ajuste cuadrático:\n";
    std::cout << "a0: " << coeficientes[0] << ", a1: " << coeficientes[1] << ", a2: " << coeficientes[2] << "\n";

    // Calcular tiempos estimados a partir del ajuste
    std::vector<double> tiemposEstimados;
    calcularTiemposEstimadosPolinomico(numeroElementos, coeficientes, tiemposEstimados);

    // Imprimir tiempos estimados
    std::cout << "\nTiempos estimados (ms):\n";
    for (size_t i = 0; i < tiemposEstimados.size(); i++) {
        std::cout << "Tamaño: " << numeroElementos[i] << ", Tiempo estimado: " << tiemposEstimados[i] << " ms\n";
    }

    // Calcular el coeficiente de determinación R^2
    double R2 = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);
    std::cout << "\nCoeficiente de determinación R^2: " << R2 << "\n";

    std::ofstream file ("bubble.txt");

    assert(file.is_open());

    for (size_t i = 0; i < 10000; i++)
    {
        file << i << " " <<calcularTiempoEstimadoPolinomico(i,coeficientes) << "\n";
    }

    file.close();
    
    return 0;
}
