#include "OrdenacionBurbuja.hpp"

void OrdenacionBurbuja(std::vector<int>& vec)
{
    bool swapped;
    size_t n = vec.size();
    for (size_t i = 0; i < n - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < n - i - 1; j++) {
            if (vec[j] > vec[j + 1]) {
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
        std::vector<int> vec(new_size);
        rellenarVector(vec);

        reloj.start();
        OrdenacionBurbuja(vec);
        reloj.stop();

        assert(estaOrdenado(vec) && "Error en la función de ordenación Burbuja\n");

        double elaped_time = static_cast<double>(reloj.elapsed());

        tiemposReales.at(i) = elaped_time;
        numeroElementos.at(i) = static_cast<double>(new_size);

        fichero << new_size << " " << elaped_time << "\n";
    }

    fichero.close();
}


void ajusteCuadratico(const std::vector<double>& numeroElementos, 
                      const std::vector<double>& tiemposReales, 
                      std::vector<double>& a)
{
    ajustePolinomicoGeneral(numeroElementos,tiemposReales,a,2); 
}



