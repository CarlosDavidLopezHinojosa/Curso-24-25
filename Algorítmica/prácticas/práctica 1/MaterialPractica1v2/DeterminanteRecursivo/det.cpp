#include "DeterminanteRecursivo.hpp"


int main() {
    int nMin = 2;   // Tamaño mínimo de la matriz
    int nMax = 11;  // Tamaño máximo de la matriz
    int repeticiones = 5; // Número de pruebas a realizar

    std::vector<double> tiemposReales;
    std::vector<double> numeroElementos;

    // Realiza pruebas con el cálculo del determinante y mide los tiempos
    tiempoDeterminanteRecursivo(nMin, nMax, repeticiones, tiemposReales, numeroElementos);

    // Imprime los tiempos de cálculo y el número de elementos
    std::cout << "Tiempos Reales de Cálculo del Determinante (ms):\n";
    for (size_t i = 0; i < tiemposReales.size(); i++) {
        std::cout << "Tamaño: " << static_cast<int>(numeroElementos[i]) 
                  << " x " << static_cast<int>(numeroElementos[i]) 
                  << ", Tiempo: " << tiemposReales[i] << " ms\n";
    }

    // Ajuste polinómico
    std::vector<double> coeficientes(2);  // a0, a1, a2 para el ajuste cuadrático
    ajusteFactorial(numeroElementos, tiemposReales, coeficientes);

    // Imprime los coeficientes del ajuste polinómico
    std::cout << "\nCoeficientes del ajuste polinómico:\n";
    for (size_t i = 0; i < coeficientes.size(); i++) {
        std::cout << "a" << i << ": " << coeficientes[i] << "\n";
    }

    // Calcular tiempos estimados a partir del ajuste polinómico
    std::vector<double> tiemposEstimados;
    calcularTiemposEstimadosFactorial(numeroElementos,coeficientes,tiemposEstimados);

    // Imprimir tiempos estimados
    std::cout << "\nTiempos estimados (ms):\n";
    for (size_t i = 0; i < tiemposEstimados.size(); i++) {
        std::cout << "Tamaño: " << static_cast<int>(numeroElementos[i]) 
                  << " x " << static_cast<int>(numeroElementos[i]) 
                  << ", Tiempo estimado: " << tiemposEstimados[i] << " ms\n";
    }

    // Calcular el coeficiente de determinación R^2
    double R2 = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);
    std::cout << "\nCoeficiente de determinación R^2: " << R2 << "\n";


    std::ofstream file ("../fact.txt");

    assert(file.is_open());

    for (size_t i = 1; i < 30; i++)
    {
        file << i << " " <<calcularTiempoEstimadoFactorial(i,coeficientes) << "\n";
    }
    return 0;
}