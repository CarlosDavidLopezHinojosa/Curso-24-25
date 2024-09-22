#include <vector>
#include <random>
#include <functional>


class Bubble_Sort_Analisis
{
public:

void rellenarVector(std::vector<int>& v);
void ordenacionSeleccion(std::vector<int>& v);
bool estaOrdenado(const std::vector<int>& v);
void tiemposOrdenacionSeleccion(int nMin, int nMax, int repeticiones, std::vector<double>& tiemposReales, std::vector<double>& numeroElementos);
void guardarDatos();
double sumatorio(std::vector<double>& n, std::vector<double>& t, int expN, int expT);
void calcularTiemposEstimadosPolinomico(const std::vector<double>& numeroElementos, const std::vector<double>& a,std::vector<double>& tiemposEstimados );
protected:

};