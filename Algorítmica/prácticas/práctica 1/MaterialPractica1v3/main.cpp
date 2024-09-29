#include <iostream>
#include <vector>
#include <cmath> // Para calcular valores
#include "funciones.hpp"

// Función para convertir microsegundos a un formato legible
void convertirTiempo(double microsegundos);

void menu();
void ordenacionBurbuja();
void productoMatricesCuadradas();
void determinanteRecursivo();

int main() 
{
    menu();
    return 0;
}

void menu() 
{
    int opcion = -1;
    
    while(opcion != 0) 
    {
        std::cout << "\n----- Menú Principal -----\n";
        std::cout << "1. Ordenación Burbuja\n";
        std::cout << "2. Producto de Matrices Cuadradas\n";
        std::cout << "3. Determinante Recursivo\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch(opcion) 
        {
            case 1:
                ordenacionBurbuja();
                break;
            case 2:
                productoMatricesCuadradas();
                break;
            case 3:
                determinanteRecursivo();
                break;
            case 0:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    }
}

void convertirTiempo(double microsegundos) 
{
    double segundos = microsegundos / 1e6;
    
    const int SECONDS_IN_MINUTE = 60;
    const int SECONDS_IN_HOUR = SECONDS_IN_MINUTE * 60;
    const int SECONDS_IN_DAY = SECONDS_IN_HOUR * 24;
    const int SECONDS_IN_WEEK = SECONDS_IN_DAY * 7;
    const int SECONDS_IN_MONTH = SECONDS_IN_DAY * 30;
    const int SECONDS_IN_YEAR = SECONDS_IN_DAY * 365;

    int años = segundos / SECONDS_IN_YEAR;
    segundos = fmod(segundos, SECONDS_IN_YEAR);

    int meses = segundos / SECONDS_IN_MONTH;
    segundos = fmod(segundos, SECONDS_IN_MONTH);

    int semanas = segundos / SECONDS_IN_WEEK;
    segundos = fmod(segundos, SECONDS_IN_WEEK);

    int días = segundos / SECONDS_IN_DAY;
    segundos = fmod(segundos, SECONDS_IN_DAY);

    int horas = segundos / SECONDS_IN_HOUR;
    segundos = fmod(segundos, SECONDS_IN_HOUR);

    int minutos = segundos / SECONDS_IN_MINUTE;
    segundos = fmod(segundos, SECONDS_IN_MINUTE);

    std::cout << "Tiempo estimado: ";
    if (años > 0) std::cout << años << " años, ";
    if (meses > 0) std::cout << meses << " meses, ";
    if (semanas > 0) std::cout << semanas << " semanas, ";
    if (días > 0) std::cout << días << " días, ";
    if (horas > 0) std::cout << horas << " horas, ";
    if (minutos > 0) std::cout << minutos << " minutos, ";
    std::cout << segundos << " segundos.\n";
}

// Implementación de la función para la ordenación burbuja
void ordenacionBurbuja() 
{
    int nMin, nMax, incremento, repeticiones;
    std::cout << "Ingrese el valor mínimo de n: ";
    std::cin >> nMin;
    std::cout << "Ingrese el valor máximo de n: ";
    std::cin >> nMax;
    std::cout << "Ingrese el incremento: ";
    std::cin >> incremento;
    std::cout << "Ingrese el número de repeticiones: ";
    std::cin >> repeticiones;

    std::vector<double> tiemposReales, numeroElementos;
    tiemposOrdenacionBurbuja(nMin, nMax, incremento, repeticiones, tiemposReales, numeroElementos);

    std::vector<double> coeficientesAjuste;
    ajusteCuadratico(numeroElementos, tiemposReales, coeficientesAjuste);

    std::vector<double> tiemposEstimados;
    calcularTiemposEstimadosPolinomico(numeroElementos, coeficientesAjuste, tiemposEstimados);

    double r2 = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

    std::cout << "\nEcuación ajustada: t(n) = " << coeficientesAjuste[0] << " + " << coeficientesAjuste[1] << " * n + " << coeficientesAjuste[2] << " * n^2\n";
    std::cout << "Coeficiente de determinación (R^2): " << r2 << "\n";

    double nEstimado;
    while(true) 
    {
        std::cout << "Ingrese el tamaño del ejemplar para estimar el tiempo (0 para salir): ";
        std::cin >> nEstimado;
        if (nEstimado == 0) break;
        
        double tiempoEstimado = calcularTiempoEstimadoPolinomico(nEstimado, coeficientesAjuste);
        convertirTiempo(tiempoEstimado); // Mostrar tiempo estimado en formato legible
    }

    guardarDatos("datosOrdenacionBurbuja.txt",numeroElementos,tiemposReales,tiemposEstimados);
}

// Implementación de la función para la multiplicación de matrices
void productoMatricesCuadradas() 
{
    int nMin, nMax, repeticiones;
    std::cout << "Ingrese el valor mínimo de n: ";
    std::cin >> nMin;
    std::cout << "Ingrese el valor máximo de n: ";
    std::cin >> nMax;
    std::cout << "Ingrese el número de repeticiones: ";
    std::cin >> repeticiones;

    std::vector<double> tiemposReales, numeroElementos;
    tiempoMultiplicacionMatrices(nMin, nMax, repeticiones, tiemposReales, numeroElementos);

    std::vector<double> coeficientesAjuste;
    ajusteCubico(numeroElementos, tiemposReales, coeficientesAjuste);

    std::vector<double> tiemposEstimados;
    calcularTiemposEstimadosPolinomico(numeroElementos, coeficientesAjuste, tiemposEstimados);

    double r2 = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

    std::cout << "\nEcuación ajustada: t(n) = " << coeficientesAjuste[0] << " + " << coeficientesAjuste[1] << " * n + " << coeficientesAjuste[2] << " * n^2 + " << coeficientesAjuste[3] << " * n^3\n";
    std::cout << "Coeficiente de determinación (R^2): " << r2 << "\n";

    double nEstimado;
    while(true) 
    {
        std::cout << "Ingrese el tamaño del ejemplar para estimar el tiempo (0 para salir): ";
        std::cin >> nEstimado;
        if (nEstimado == 0) break;
        
        double tiempoEstimado = calcularTiempoEstimadoPolinomico(nEstimado, coeficientesAjuste);
        convertirTiempo(tiempoEstimado); // Mostrar tiempo estimado en formato legible
    }

    guardarDatos("datosMultiplicacionMatrices.txt",numeroElementos,tiemposReales,tiemposEstimados);
}

// Implementación de la función para el cálculo del determinante recursivo
void determinanteRecursivo() 
{
    int nMin, nMax, repeticiones;
    std::cout << "Ingrese el valor mínimo de n: ";
    std::cin >> nMin;
    std::cout << "Ingrese el valor máximo de n: ";
    std::cin >> nMax;
    std::cout << "Ingrese el número de repeticiones: ";
    std::cin >> repeticiones;

    std::vector<double> tiemposReales, numeroElementos;
    tiempoDeterminanteRecursivo(nMin, nMax, repeticiones, tiemposReales, numeroElementos);

    std::vector<double> coeficientesAjuste;
    ajusteFactorial(numeroElementos, tiemposReales, coeficientesAjuste);

    std::vector<double> tiemposEstimados;
    calcularTiemposEstimadosFactorial(numeroElementos, coeficientesAjuste, tiemposEstimados);

    double r2 = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

    std::cout << "\nEcuación ajustada: t(n) = " << coeficientesAjuste[0] << " + " << coeficientesAjuste[1] << " * n!\n";
    std::cout << "Coeficiente de determinación (R^2): " << r2 << "\n";

    double nEstimado;
    while(true) 
    {
        std::cout << "Ingrese el tamaño del ejemplar para estimar el tiempo (0 para salir): ";
        std::cin >> nEstimado;
        if (nEstimado == 0) break;
        
        double tiempoEstimado = calcularTiempoEstimadoFactorial(nEstimado, coeficientesAjuste);
        convertirTiempo(tiempoEstimado); // Mostrar tiempo estimado en formato legible
    }

    guardarDatos("datosDeterminantesRecursivo.txt",numeroElementos,tiemposReales,tiemposEstimados);
}
