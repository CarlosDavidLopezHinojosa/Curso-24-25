#include "funciones.hpp"

// Implementación de las funciones que utilizaremos para todos los ajuste de complejidad

void rellenarVector(std::vector<int>& vec)
{
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<int> value(0, 9999999);
    
    for (int& val : vec)
        val = value(gen);
}

void rellenarMatriz(std::vector<std::vector<double>>& A)
{
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_real_distribution<double> value(0.95,1.05);

    for (size_t i = 0; i < A.size(); i++)
        for (size_t j = 0; j < A.size(); j++)
            A[i][j] = value(gen);
}

double sumatorio(std::vector<double>& n, std::vector<double>& t, int expN, int expT)
{
    assert(n.size() == t.size() && "El tamaño de los vectores de tamaños y tiempos no coincide (sumatorio)\n");

    size_t size = n.size();
    double suma = 0;

    for (size_t i = 0; i < size; i++)
        suma += std::pow(n.at(i),expN) * std::pow(t.at(i),expT);
    
    return suma;
}

long double calcularTiempoEstimadoPolinomico(const long double& n,const std::vector<double>& a)
{
    size_t cSize = a.size();
    double est = 0;

    for (size_t i = 0; i < cSize; i++)
            est += a[i] * std::pow(n,i);
    return est;
}

void calcularTiemposEstimadosPolinomico(const std::vector<double>& numeroElementos, 
                                        const std::vector<double>& a, 
                                        std::vector<double>& tiemposEstimados)
{
    size_t nSize = numeroElementos.size();
    tiemposEstimados.resize(nSize,0);

    for (size_t i = 0; i < nSize; i++)
        tiemposEstimados[i] += calcularTiempoEstimadoPolinomico(numeroElementos[i],a);

}


void ajustePolinomicoGeneral(const std::vector<double>& numeroElementos, 
                             const std::vector<double>& tiemposReales, 
                             std::vector<double>& a, 
                             int grado_del_polinomio)
{
    assert(numeroElementos.size() == tiemposReales.size() 
           && "El tamaño de los vectores de tamaños y tiempos no coincide (ajusteGeneral)\n");

    std::vector<double> nVec = numeroElementos;
    std::vector<double> tVec= tiemposReales;
    a.resize(grado_del_polinomio + 1);
    size_t num_coef = static_cast<size_t>(grado_del_polinomio + 1);

    std::vector<std::vector<double>> A(num_coef,std::vector<double>(num_coef)); //num_coef x num_coef
    std::vector<std::vector<double>> B(num_coef,std::vector<double>(1)); //num_coef x 1
    std::vector<std::vector<double>> X(num_coef,std::vector<double>(1)); //num_coef x 1


    for (size_t i = 0; i < num_coef; i++)
    {
        for (size_t j = 0; j < num_coef; j++)
        {
                A[i][j] = sumatorio(nVec,tVec,static_cast<int>(i+j),0);
                B[i][0] = sumatorio(nVec,tVec,static_cast<int>(i),1);
        }
    }
        
    resolverSistemaEcuaciones(A,B,static_cast<int>(num_coef),X);

    for (size_t i = 0; i < num_coef; i++)
        a[i] = X[i][0];   
}


double media(const std::vector<double>& vectorTiempos)
{
    return std::accumulate(vectorTiempos.begin(),vectorTiempos.end(),0) / vectorTiempos.size();
}

double varianza(const std::vector<double>& vectorTiempos)
{
    double var = 0.0;
    double med = media(vectorTiempos);
    size_t n = vectorTiempos.size();

    for (size_t i = 0; i < n; i++)
        var += (vectorTiempos.at(i) - med) * (vectorTiempos.at(i) - med);

    return var / n;
}

double calcularCoeficienteDeterminacion(const std::vector<double>& tiemposReales, 
                                        const std::vector<double>& tiemposEstimados)
{
    return varianza(tiemposEstimados) / varianza(tiemposReales);
}


void guardarDatos(std::string nombre_fichero,
                  std::vector<double>& numeroElementos,
                  std::vector<double>& tiemposReales, 
                  std::vector<double>& tiemposEstimados)
{
    std::ofstream fichero(nombre_fichero);
    assert(fichero.is_open());

    for (size_t i = 0; i < tiemposReales.size(); i++)
        fichero << numeroElementos[i] << " " 
                << tiemposReales[i] << " " 
                << tiemposEstimados[i] << "\n";

    fichero.close();
    assert(!fichero.is_open());
}


//Implementación de las funciones para realizar el analisis de complejidad de la Ordenación burbuja O(n^2)

void OrdenacionBurbuja(std::vector<int>& vec)
{
    bool swapped;
    size_t n = vec.size();
    for (size_t i = 0; i < n - 1; i++) 
    {
        swapped = false;
        for (size_t j = 0; j < n - i - 1; j++) 
        {
            if (vec[j] > vec[j + 1]) 
            {
                std::swap(vec[j], vec[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

bool estaOrdenado(const std::vector<int>& vec)
{
    return is_sorted(vec.begin(),vec.end());
}


void tiemposOrdenacionBurbuja(int nMin, int nMax, int repeticiones,
                              int incremento,
                              std::vector<double>& tiemposReales, 
                              std::vector<double>& numeroElementos)
{

    size_t n = 1 + (nMax - nMin) / incremento;

    tiemposReales.resize(n);
    numeroElementos.resize(n);

    Clock reloj;
    size_t curr = 0;
    for (size_t i = nMin; i <= nMax; i += incremento)
    {   
        double media_tiempo = 0.0;
        for (size_t j = 0; j < repeticiones; j++)
        {
            std::vector<int> vec(i);
            rellenarVector(vec);

            reloj.start();
            OrdenacionBurbuja(vec);
            reloj.stop();

            //assert(estaOrdenado(vec) && "Error en la función de ordenación Burbuja\n");

            double elaped_time = static_cast<double>(reloj.elapsed());

            media_tiempo += elaped_time;
        }

        media_tiempo /= repeticiones;

        tiemposReales.at(curr) = media_tiempo;
        numeroElementos.at(curr++) = static_cast<double>(i);

        double porcentaje = (static_cast<double>(curr) / n) * 100.0;
        std::cout << "\r\tProgreso: " << porcentaje << "% completado con n = " << i << "          " << std::flush;
    }
}


void ajusteCuadratico(const std::vector<double>& numeroElementos, 
                      const std::vector<double>& tiemposReales, 
                      std::vector<double>& a)
{
    ajustePolinomicoGeneral(numeroElementos,tiemposReales,a,2); 
}



// Implementación de las funciones para realizar el analisis de complejidad de la Multiplicación de Matrices de orden n O(n^3)


void MultiplicacionMatrices(std::vector<std::vector<double>>& A, 
                            std::vector<std::vector<double>>& B, 
                            std::vector<std::vector<double>>& C)
{
    multiplicarMatrices(A,B,C);
}

void tiempoMultiplicacionMatrices(int nMin, int nMax, int incremento, 
                                  std::vector<double>& tiemposReales, 
                                  std::vector<double>& numeroElementos)
{

    size_t n = 1 + (nMax - nMin) / incremento;
    tiemposReales.resize(n);
    numeroElementos.resize(n);

    Clock reloj;
    size_t curr = 0;
    
    for (size_t i = nMin; i <= nMax; i += incremento)
    {
        std::vector<std::vector<double>> A(i,std::vector<double>(i)),
                                         B(i,std::vector<double>(i)),
                                         C(i,std::vector<double>(i));

        rellenarMatriz(A);
        rellenarMatriz(B);

            reloj.start();
            MultiplicacionMatrices(A,B,C);
            reloj.stop();

        double elaped_time = static_cast<double>(reloj.elapsed());

        tiemposReales.at(curr) = static_cast<double>(elaped_time);
        numeroElementos.at(curr++) = static_cast<double>(i);

        double porcentaje = (static_cast<double>(curr) / n) * 100.0;
        std::cout << "\r\tProgreso: " << porcentaje << "% completado con n = " << i << "          " << std::flush;
    }
}

void ajusteCubico(const std::vector<double>& numeroElementos, 
                  const std::vector<double>& tiemposReales, 
                  std::vector<double>& a)
{
    ajustePolinomicoGeneral(numeroElementos,tiemposReales,a,3);
}


// Implementación de las funciones para realizar el analisis de complejidad del calculo del determinate de manera recursiva O(n!)

double DeterminanteRecursivo(const std::vector<std::vector<double>>& m, int n) 
{
    // Base de la recursión: matriz de orden 2x2
    if (n == 1)
    {
        return m[0][0];
    }
    
    if (n == 2) 
    {
        return m[0][0] * m[1][1] - m[1][0] * m[0][1];
    }

    if (n == 3)
    {
        return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) - 
               m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) + 
               m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }
    
    
    // Caso recursivo: matriz de orden mayor que 2
    double determinante = 0;
    int signo = 1; // +1 o -1 según la posición en la diagonal principal
    for (int i = 0; i < n; i++) 
    {
        // Crear submatriz excluyendo la primera fila y la i-ésima columna
        std::vector<std::vector<double>> submatrix(n - 1, std::vector<double>(n - 1));
        for (int j = 1; j < n; j++) 
        {
            int sub_col = 0; // índice de columna de la submatriz
            for (int k = 0; k < n; k++) 
            {
                if (k == i) continue; // Excluir la columna i
                submatrix[j - 1][sub_col] = m[j][k];
                sub_col++;
            }
        }
        // Calcular el determinante de la submatriz
        double subdet = DeterminanteRecursivo(submatrix, n - 1);
        determinante += signo * m[0][i] * subdet;
        signo *= -1; // Cambiar signo para la próxima iteración
    }
    return determinante;
}


void tiempoDeterminanteRecursivo(int nMin, int nMax, int incremento, 
                                 std::vector<double>& tiemposReales, 
                                 std::vector<double>& numeroElementos)
{
    size_t n = 1 + (nMax - nMin) / incremento;
    tiemposReales.resize(n);
    numeroElementos.resize(n);

    Clock reloj;
    size_t curr = 0;

    for (size_t i = nMin; i <= nMax; i += incremento)
    {

        std::vector<std::vector<double>> A(i,std::vector<double>(i));
        rellenarMatriz(A);

            reloj.start();
            DeterminanteRecursivo(A,A.size());
            reloj.stop();

        double elaped_time = static_cast<double>(reloj.elapsed());

        tiemposReales.at(curr) = elaped_time;
        numeroElementos.at(curr++) = static_cast<double>(i);

        double porcentaje = (static_cast<double>(curr) / n) * 100.0;
        std::cout << "\r\tProgreso: " << porcentaje << "% completado con n = " << i << "          " << std::flush;
    }
}

double sumatorioFactorial(std::vector<double>& n, std::vector<double>& t, int expN, int expT)
{
    assert(n.size() == t.size() && "El tamaño de los vectores de tamaños y tiempos no coincide (sumatorio)\n");

    size_t size = n.size();
    double suma = 0;

    for (size_t i = 0; i < size; i++)
        suma += std::pow(tgamma(n.at(i) + 1),expN) * std::pow(t.at(i),expT);
    
    return suma;
}

void ajusteFactorial(const std::vector<double>& numeroElementos, 
                     const std::vector<double>& tiemposReales, 
                     std::vector<double>& a)
{
    assert(numeroElementos.size() == tiemposReales.size() 
           && "El tamaño de los vectores de tamaños y tiempos no coincide (ajusteGeneral)\n");

    std::vector<double> nVec = numeroElementos;
    std::vector<double> tVec= tiemposReales;
    a.resize(2);
    size_t num_coef = static_cast<size_t>(2);

    std::vector<std::vector<double>> A(num_coef,std::vector<double>(num_coef)); //num_coef x num_coef
    std::vector<std::vector<double>> B(num_coef,std::vector<double>(1)); //num_coef x 1
    std::vector<std::vector<double>> X(num_coef,std::vector<double>(1)); //num_coef x 1


    for (size_t i = 0; i < num_coef; i++)
    {
        for (size_t j = 0; j < num_coef; j++)
        {
                A[i][j] = sumatorioFactorial(nVec,tVec,static_cast<int>(i+j),0);
                B[i][0] = sumatorioFactorial(nVec,tVec,static_cast<int>(i),1);
        }
    }
        
    resolverSistemaEcuaciones(A,B,static_cast<int>(num_coef),X);

    for (size_t i = 0; i < num_coef; i++)
        a[i] = X[i][0];   
}


long double calcularTiempoEstimadoFactorial(const long double &n, const std::vector<double>& a)
{
    return a[0] + a[1] * tgamma(static_cast<int>(n)+1);
}

void calcularTiemposEstimadosFactorial(const std::vector<double>& numeroElementos, 
                                       const std::vector<double>& a, 
                                       std::vector<double>& tiemposEstimados)
{
    size_t nSize = numeroElementos.size();
    tiemposEstimados.resize(nSize,0);

    for (size_t i = 0; i < nSize; i++)
        tiemposEstimados[i] += calcularTiempoEstimadoFactorial(numeroElementos[i],a);
}