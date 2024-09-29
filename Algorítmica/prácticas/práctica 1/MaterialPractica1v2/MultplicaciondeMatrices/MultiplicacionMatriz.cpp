#include "MultiplicacionMatriz.hpp"

void MultiplicacionMatrices(std::vector<std::vector<double>>& A, 
                            std::vector<std::vector<double>>& B, 
                            std::vector<std::vector<double>>& C)
{
    for(size_t i = 0; i < A.size(); i++) //Recorre filas de la primera matriz
	{
		for(size_t j = 0; j < B[0].size(); j++) //Recorre columnas de la segunda matriz
		{
			C[i][j] = 0.0;
			for(size_t k = 0; k < A[0].size(); k++) //Recorre los elementos a multiplicar (numero de columnas de la primera matriz)
				C[i][j] = C [i][j] + A[i][k]*B[k][j];
		}
	}
}

void tiempoMultiplicacionMatrices(int nMin, int nMax, int repeticiones, 
                       std::vector<double>& tiemposReales, 
                       std::vector<double>& numeroElementos)
{
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<size_t> randSize(nMin,nMax);

    tiemposReales.resize(repeticiones);
    numeroElementos.resize(repeticiones);

    Clock reloj;
    std::ofstream fichero("tiemposReales.txt");

    assert(fichero.is_open() && "No se pudo abrir el fichero tiemposReales.txt\n");

    for (size_t i = 0; i < repeticiones; i++)
    {
        size_t new_size = randSize(gen);
        std::vector<std::vector<double>> A(new_size,std::vector<double>(new_size)),
                                         B(new_size,std::vector<double>(new_size)),
                                         C(new_size,std::vector<double>(new_size));

        rellenarMatriz(A);
        rellenarMatriz(B);
        
        reloj.start();
        MultiplicacionMatrices(A,B,C);
        reloj.stop();

        double elaped_time = static_cast<double>(reloj.elapsed());

        tiemposReales.at(i) = elaped_time;
        numeroElementos.at(i) = static_cast<double>(new_size);

        fichero << new_size << " " << elaped_time << "\n";
    }

    fichero.close();
}

void ajusteCubico(const std::vector<double>& numeroElementos, 
                      const std::vector<double>& tiemposReales, 
                      std::vector<double>& a)
{
    ajustePolinomicoGeneral(numeroElementos,tiemposReales,a,3);
}