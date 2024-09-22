#include "algorithmics_utils.hpp" // Asegúrate de que este archivo esté en la misma carpeta

// Función de Bubble Sort
void bubble_sort(std::vector<int>& arr) {
    bool swapped;
    int n = arr.size();
    do 
    {
        swapped = false;
        for (int i = 0; i < n - 1; i++) 
        {
            if (arr[i] > arr[i + 1]) 
            {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        n--;
    } while (swapped);
}

void quick_sort(std::vector<int>& v)
{
    std::sort(v.begin(),v.end());
}

int main() 
{
    // Crear una instancia de QuadraticComplexity para el algoritmo
    QuadraticComplexity<int, std::function<void(std::vector<int>&)>> complexity(quick_sort);

    // Calcular complejidad
    int max_size = 1000; // Tamaño máximo de la entrada
    int min_size = 10;   // Tamaño mínimo de la entrada
    int iterations = 200; // Número de iteraciones para medir

    complexity.calculate_complexity(max_size, min_size, iterations);
    complexity.calculate_statistics();

    // Imprimir resultados
    std::cout << "Media Real: " << complexity.real_median() << " microsegundos\n";
    std::cout << "Media Calculada: " << complexity.calculated_median() << " microsegundos\n";
    std::cout << "Varianza Real: " << complexity.real_variance() << "\n";
    std::cout << "Varianza Calculada: " << complexity.calculated_variance() << "\n";
    std::cout << "Desviación Estándar Real: " << complexity.real_std_dev() << "\n";
    std::cout << "Desviación Estándar Calculada: " << complexity.calculated_std_dev() << "\n";
    std::cout << "Determinación: " << complexity.determinance() << "\n";

    complexity.load_datafile("Datos.txt");
    return 0;
}
