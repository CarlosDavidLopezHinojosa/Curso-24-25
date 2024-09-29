#include "common.hpp"

void rellenarVector(std::vector<int>& vec)
{
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<int> value(0, 9999999);
    
    for (int& val : vec)
        val = value(gen);
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

double calcularTiempoEstimadoPolinomico(const double& n,const std::vector<double>& a)
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
    std::ofstream fichero("tiemposEstimados.txt");

    assert(fichero.is_open() && "No se pudo abrir el fichero tiemposEstimados.txt\n");

    for (size_t i = 0; i < nSize; i++)
    {
        tiemposEstimados[i] += calcularTiempoEstimadoPolinomico(numeroElementos[i],a);
        fichero << numeroElementos[i] << " " << tiemposEstimados[i] << "\n";
    }

    fichero.close();
}


void ajustePolinomicoGeneral(const std::vector<double>& numeroElementos, 
                      const std::vector<double>& tiemposReales, 
                      std::vector<double>& a, int grado_del_polinomio)
{
    assert(numeroElementos.size() == tiemposReales.size() 
           && "El tamaño de los vectores de tamaños y tiempos no coincide (ajusteGeneral)\n");

    std::vector<double> nVec = numeroElementos;
    std::vector<double> tVec= tiemposReales;
    a.resize(grado_del_polinomio+1);
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

double calcularCoeficienteDeterminacion(const std::vector<double>& tiemposReales, 
                      const std::vector<double>& tiemposEstimados)
{
    double SST = 0;
    double SSR = 0;
    double media = 0;
    std::valarray<double> Real(tiemposReales.data(),tiemposReales.size());
    std::valarray<double> Est(tiemposEstimados.data(),tiemposEstimados.size());
    std::valarray<double> e_2,e_prima_2;

    media = Real.sum()/static_cast<double>(Real.size());
    e_2 = std::pow(Real - media,2);
    e_prima_2 = std::pow(Real - Est,2);

    SST = e_2.sum();
    SSR = e_prima_2.sum();

    return 1 - SSR/SST;
}

void rellenarMatriz(std::vector<std::vector<double>>& A)
{
    std::random_device seed;
    std::mt19937 gen;
    std::uniform_real_distribution<double> value(0.95,1.05);

    for (size_t i = 0; i < A.size(); i++)
        for (size_t j = 0; j < A.size(); j++)
            A[i][j] = value(gen);
}