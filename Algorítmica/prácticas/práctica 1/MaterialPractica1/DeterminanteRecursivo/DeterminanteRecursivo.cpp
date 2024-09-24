#include "DeterminanteRecursivo.hpp"

double DeterminanteRecursivo(const std::vector<std::vector<double>>& m, int n) 
{
    // Base de la recursión: matriz de orden 2x2
    if (n == 2) 
    {
        return m[0][0] * m[1][1] - m[1][0] * m[0][1];
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


void tiempoDeterminanteRecursivo(int nMin, int nMax, int repeticiones, 
                       std::vector<double>& tiemposReales, 
                       std::vector<double>& numeroElementos)
{
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<size_t> randSize(nMin,nMax);

    tiemposReales.resize(repeticiones);
    numeroElementos.resize(repeticiones);

    Clock reloj;
    std::ofstream fichero("tiemposRealesFactorial.txt");

    assert(fichero.is_open() && "No se pudo abrir el fichero tiemposReales.txt\n");

    for (size_t i = 0; i < repeticiones; i++)
    {
        size_t new_size = randSize(gen);
        std::vector<std::vector<double>> A(new_size,std::vector<double>(new_size));

        rellenarMatriz(A);
        
        reloj.start();
        DeterminanteRecursivo(A,A.size());
        reloj.stop();

        double elaped_time = static_cast<double>(reloj.elapsed());

        tiemposReales.at(i) = elaped_time;
        numeroElementos.at(i) = static_cast<double>(new_size);

        fichero << new_size << " " << elaped_time << "\n";
    }

    fichero.close();
}

void ajusteFactorial(const std::vector<double>& numeroElementos, 
                      const std::vector<double>& tiemposReales, 
                      std::vector<double>& a)
{
    ajustePolinomicoGeneral(numeroElementos,tiemposReales,a,1);
}


double  calcularTiempoEstimadoFactorial(const double &n, const std::vector<double>& a)
{
    return a[0] + a[1] * tgamma(static_cast<int>(n)+1);
}

void calcularTiemposEstimadosFactorial(const std::vector<double>& numeroElementos, 
                      const std::vector<double>& a, 
                      std::vector<double>& tiemposEstimados)
{
    size_t nSize = numeroElementos.size();
    tiemposEstimados.resize(nSize,0);
    std::ofstream fichero("tiemposFactorialEstimados.txt");

    assert(fichero.is_open() && "No se pudo abrir el fichero tiemposEstimados.txt\n");

    for (size_t i = 0; i < nSize; i++)
    {
        tiemposEstimados[i] += calcularTiempoEstimadoFactorial(numeroElementos[i],a);
        fichero << numeroElementos[i] << " " << tiemposEstimados[i] << "\n";
    }

    fichero.close();
}