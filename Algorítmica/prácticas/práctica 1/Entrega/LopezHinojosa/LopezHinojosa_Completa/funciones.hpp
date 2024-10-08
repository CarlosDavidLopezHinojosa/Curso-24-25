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
 
/**
 * @brief Rellena un vector con valores enteros aleatorios 
 * @param vec  Vector a rellenar
 * @return vec Vector rellenado
 */
void rellenarVector(std::vector<int>& vec);

/**
 * @brief Rellena una matriz con valores reales aleatorios 
 * @param A  Matriz a rellenar
 * @return A Matriz rellenada
 */
void rellenarMatriz(std::vector<std::vector<double>>& A);

/**
 * @brief Calcula el sumatorio de la siguiente manera:
 * 
 * @param n Vector de elementos n
 * @param t Vector de elementos t
 * @param expN Exponente para el vector n
 * @param expT Exponente para el vector t
 * 
 * @return Resultado del sumatorio como un valor double
 */
double sumatorio(std::vector<double>& n, std::vector<double>& t, int expN, int expT);

/**
 * @brief Calcula el tiempo estimado para una función polinómica.
 * 
 * El cálculo se basa en la fórmula del polinomio de ajuste:
 * t(n) = a0 + a1 * n + a2 * n^2 + ... + ak * n^k
 * 
 * @param n Tamaño del ejemplar.
 * @param a Coeficientes del polinomio.
 * 
 * @return El tiempo estimado en función del tamaño del ejemplar.
 */
long double calcularTiempoEstimadoPolinomico(const long double& n, const std::vector<double>& a);

/**
 * @brief Calcula los tiempos estimados para un conjunto de elementos.
 * 
 * Utiliza los coeficientes obtenidos de un polinomio de ajuste para estimar
 * el tiempo de ejecución para cada tamaño de ejemplar.
 * 
 * @param numeroElementos Vector con los diferentes tamaños de ejemplar.
 * @param a Coeficientes del polinomio de ajuste.
 * @param tiemposEstimados Vector donde se guardarán los tiempos estimados.
 */
void calcularTiemposEstimadosPolinomico(const std::vector<double>& numeroElementos, 
                                        const std::vector<double>& a, 
                                        std::vector<double>& tiemposEstimados);

/**
 * @brief Realiza el ajuste polinómico de grado general para los tiempos de ejecución.
 * 
 * Ajusta una función polinómica de grado especificado para los tiempos de ejecución
 * obtenidos a partir de un conjunto de tamaños de ejemplares.
 * 
 * @param numeroElementos Vector con los diferentes tamaños de ejemplar.
 * @param tiemposReales Vector con los tiempos de ejecución reales.
 * @param a Vector donde se almacenarán los coeficientes del polinomio de ajuste.
 * @param grado_del_polinomio Grado del polinomio de ajuste.
 */
void ajustePolinomicoGeneral(const std::vector<double>& numeroElementos, 
                             const std::vector<double>& tiemposReales, 
                             std::vector<double>& a, 
                             int grado_del_polinomio);

/**
 * @brief Calcula la media aritmética de un Vector de tiempos
 * 
 * @param vectorTiempos Vector que almacena los tiempos estimado o reales de un ajuste polinómico
 * 
 * @return La media de tiempos μ
 */
double media(const std::vector<double>& vectorTiempos);

/**
 * @brief Calcula varianza de un Vector de tiempos
 * 
 * @param vectorTiempos Vector que almacena los tiempos estimado o reales de un ajuste polinómico
 * 
 * @return La varianza de tiempos σ^2
 */
double varianza(std::vector<double>& vectorTiempos);

/**
 * @brief Calcula el coeficiente de determinación (R²) para el ajuste polinómico.
 * 
 * Compara los tiempos estimados con los tiempos reales para determinar la precisión
 * del ajuste polinómico.
 * 
 * @param tiemposReales Vector con los tiempos de ejecución reales.
 * @param tiemposEstimados Vector con los tiempos estimados.
 * 
 * @return El coeficiente de determinación (R²).
 */
double calcularCoeficienteDeterminacion(const std::vector<double>& tiemposReales, 
                                        const std::vector<double>& tiemposEstimados);

/**
 * @brief Guarda los datos en un archivo de texto.
 * 
 * Escribe los tamaños de ejemplar, los tiempos reales y los tiempos estimados en
 * un archivo para poder visualizarlos o analizarlos posteriormente.
 * 
 * @param nombre_fichero Nombre del archivo donde se guardarán los datos.
 * @param numeroElementos Vector con los tamaños de ejemplar.
 * @param tiemposReales Vector con los tiempos reales.
 * @param tiemposEstimados Vector con los tiempos estimados.
 */
void guardarDatos(std::string nombre_fichero,
                  std::vector<double>& numeroElementos,
                  std::vector<double>& tiemposReales, 
                  std::vector<double>& tiemposEstimados);


// Definición de las funciones para realizar el análisis de complejidad de la Ordenación burbuja O(n^2)

/**
 * @brief Realiza la ordenación burbuja sobre un vector de enteros.
 * 
 * @param vec Vector de enteros a ordenar.
 */
void OrdenacionBurbuja(std::vector<int>& vec);

/**
 * @brief Comprueba si un vector está ordenado.
 * 
 * @param vec Vector de enteros a comprobar.
 * @return true si el vector está ordenado, false en caso contrario.
 */
bool estaOrdenado(const std::vector<int>& vec);

/**
 * @brief Calcula los tiempos de ejecución para la ordenación burbuja.
 * 
 * Realiza pruebas de la ordenación burbuja para diferentes tamaños de ejemplares y 
 * repeticiones, y guarda los tiempos obtenidos.
 * 
 * @param nMin Tamaño mínimo del vector a ordenar.
 * @param nMax Tamaño máximo del vector a ordenar.
 * @param repeticiones Número de repeticiones para cada tamaño de vector.
 * @param incremento Incremento entre cada tamaño de vector.
 * @param tiemposReales Vector donde se almacenarán los tiempos reales.
 * @param numeroElementos Vector donde se almacenarán los tamaños de los ejemplares.
 */
void tiemposOrdenacionBurbuja(int nMin, int nMax, int repeticiones, int incremento, 
                              std::vector<double>& tiemposReales, 
                              std::vector<double>& numeroElementos);

/**
 * @brief Realiza el ajuste cuadrático para los tiempos de ejecución de la ordenación burbuja.
 * 
 * Ajusta una función cuadrática (de grado 2) a los tiempos obtenidos durante las pruebas de 
 * ordenación burbuja.
 * 
 * @param numeroElementos Vector con los tamaños de los ejemplares.
 * @param tiemposReales Vector con los tiempos de ejecución reales.
 * @param a Vector donde se almacenarán los coeficientes del polinomio de ajuste.
 */
void ajusteCuadratico(const std::vector<double>& numeroElementos, 
                      const std::vector<double>& tiemposReales, 
                      std::vector<double>& a);


// Definición de las funciones para realizar el análisis de complejidad de la Multiplicación de Matrices O(n^3)

/**
 * @brief Realiza la multiplicación de dos matrices cuadradas.
 * 
 * @param A Primera matriz a multiplicar.
 * @param B Segunda matriz a multiplicar.
 * @param C Matriz resultado de la multiplicación.
 */
void MultiplicacionMatrices(std::vector<std::vector<double>>& A, 
                            std::vector<std::vector<double>>& B, 
                            std::vector<std::vector<double>>& C);

/**
 * @brief Calcula los tiempos de ejecución para la multiplicación de matrices cuadradas.
 * 
 * Realiza pruebas de multiplicación de matrices para diferentes tamaños y guarda los
 * tiempos obtenidos.
 * 
 * @param nMin Tamaño mínimo de las matrices.
 * @param nMax Tamaño máximo de las matrices.
 * @param repeticiones Número de repeticiones para cada tamaño de matrices.
 * @param tiemposReales Vector donde se almacenarán los tiempos reales.
 * @param numeroElementos Vector donde se almacenarán los tamaños de las matrices.
 */
void tiempoMultiplicacionMatrices(int nMin, int nMax, int incremento,
                                  std::vector<double>& tiemposReales, 
                                  std::vector<double>& numeroElementos);

/**
 * @brief Realiza el ajuste cúbico para los tiempos de ejecución de la multiplicación de matrices.
 * 
 * Ajusta una función cúbica (de grado 3) a los tiempos obtenidos durante las pruebas de 
 * multiplicación de matrices.
 * 
 * @param numeroElementos Vector con los tamaños de las matrices.
 * @param tiemposReales Vector con los tiempos de ejecución reales.
 * @param a Vector donde se almacenarán los coeficientes del polinomio de ajuste.
 */
void ajusteCubico(const std::vector<double>& numeroElementos, 
                  const std::vector<double>& tiemposReales, 
                  std::vector<double>& a);


// Definición de las funciones para realizar el análisis de complejidad del cálculo del determinante recursivo O(n!)

/**
 * @brief Calcula el determinante de una matriz de forma recursiva.
 * 
 * @param m Matriz de la cual se quiere calcular el determinante.
 * @param n Dimensión de la matriz.
 * @return El determinante de la matriz.
 */
double DeterminanteRecursivo(const std::vector<std::vector<double>>& m, int n);

/**
 * @brief Calcula los tiempos de ejecución para el cálculo del determinante recursivo.
 * 
 * Realiza pruebas del cálculo del determinante para diferentes tamaños de matrices y
 * guarda los tiempos obtenidos.
 * 
 * @param nMin Tamaño mínimo de las matrices.
 * @param nMax Tamaño máximo de las matrices.
 * @param repeticiones Número de repeticiones para cada tamaño de matrices.
 * @param tiemposReales Vector donde se almacenarán los tiempos reales.
 * @param numeroElementos Vector donde se almacenarán los tamaños de las matrices.
 */
void tiempoDeterminanteRecursivo(int nMin, int nMax, int incremento,
                                 std::vector<double>& tiemposReales, 
                                 std::vector<double>& numeroElementos);

/**
 * @brief Calcula el sumatorio con factoriales para ajuste de funciones.
 * 
 * Realiza el cálculo del sumatorio en el ajuste factorial, considerando el uso de factoriales
 * en los exponentes de los vectores de entrada.
 * 
 * @param n Vector de tamaños de ejemplares.
 * @param t Vector de tiempos reales.
 * @param expN Exponente para el vector n.
 * @param expT Exponente para el vector t.
 * @return Resultado del sumatorio.
 */
double sumatorioFactorial(std::vector<double>& n, std::vector<double>& t, int expN, int expT);

/**
 * @brief Realiza el ajuste factorial para los tiempos de ejecución del cálculo del determinante recursivo.
 * 
 * Ajusta una función de tipo factorial a los tiempos obtenidos durante las pruebas de 
 * cálculo del determinante recursivo.
 * 
 * @param numeroElementos Vector con los tamaños de las matrices.
 * @param tiemposReales Vector con los tiempos de ejecución reales.
 * @param a Vector donde se almacenarán los coeficientes del ajuste factorial.
 */
void ajusteFactorial(const std::vector<double>& numeroElementos, 
                     const std::vector<double>& tiemposReales, 
                     std::vector<double>& a);

/**
 * @brief Calcula el tiempo estimado para una función factorial.
 * 
 * Estima el tiempo de ejecución en función del tamaño del ejemplar usando una función de ajuste factorial.
 * 
 * @param n Tamaño del ejemplar.
 * @param a Coeficientes del ajuste factorial.
 * 
 * @return El tiempo estimado en función del tamaño del ejemplar.
 */
long double calcularTiempoEstimadoFactorial(const long double &n, const std::vector<double>& a);

/**
 * @brief Calcula los tiempos estimados para un conjunto de elementos, basado en una función factorial.
 * 
 * Utiliza los coeficientes obtenidos de un ajuste factorial para estimar el tiempo de ejecución
 * para cada tamaño de ejemplar.
 * 
 * @param numeroElementos Vector con los diferentes tamaños de ejemplar.
 * @param a Coeficientes del ajuste factorial.
 * @param tiemposEstimados Vector donde se guardarán los tiempos estimados.
 */
void calcularTiemposEstimadosFactorial(const std::vector<double>& numeroElementos, 
                                       const std::vector<double>& a, 
                                       std::vector<double>& tiemposEstimados);

#endif
