#include "algorithmics_utils.hpp"

// Función para realizar el algoritmo Bubble Sort
void bubble_sort(std::vector<int>& arr) {
    bool swapped;
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // Si no se hizo ningún intercambio, el array ya está ordenado
        if (!swapped) break;
    }
}

// Función para generar vectores aleatorios de tamaño 'size'
std::tuple<std::vector<int>&> generate_random_vector(int size) {
    static std::vector<int> random_vector;
    random_vector.clear();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 10000); // Números aleatorios entre 0 y 10000
    
    for (int i = 0; i < size; ++i) {
        random_vector.push_back(dist(gen));
    }
    return std::tie(random_vector);
}

// Función para probar el algoritmo Bubble Sort y medir la complejidad
void test_bubble_sort_complexity() {
    // Creamos el objeto PolynomialComplexity con el algoritmo Bubble Sort y el generador de vectores aleatorios
    PolynomialComplexity<void, std::vector<int>> bubble_sort_complexity(
        bubble_sort,              // Algoritmo a medir
        generate_random_vector,   // Generador de datos aleatorios
        2                         // Grado del polinomio (Bubble Sort tiene complejidad O(n^2))
    );

    int min_size = 100;    // Tamaño mínimo del vector
    int max_size = 1000;   // Tamaño máximo del vector
    int iterations = 20;   // Número de iteraciones para la prueba

    // Calculamos la complejidad del algoritmo
    bubble_sort_complexity.calculate_complexity(min_size, max_size, iterations);

    // Calculamos las estadísticas (media, varianza, etc.)
    bubble_sort_complexity.calculate_statistics();

    // Mostramos los resultados
    std::cout << "Bubble Sort Complexity Analysis:" << std::endl;
    std::cout << "Real Mean Time: " << bubble_sort_complexity.real_mean() << " microseconds" << std::endl;
    std::cout << "Calculated Mean Time: " << bubble_sort_complexity.calculated_mean() << " microseconds" << std::endl;
    std::cout << "Real Variance: " << bubble_sort_complexity.real_variance() << std::endl;
    std::cout << "Calculated Variance: " << bubble_sort_complexity.calculated_variance() << std::endl;
    std::cout << "Real Standard Deviation: " << bubble_sort_complexity.real_std_dev() << std::endl;
    std::cout << "Calculated Standard Deviation: " << bubble_sort_complexity.calculated_std_dev() << std::endl;
    std::cout << "Determination Coefficient: " << bubble_sort_complexity.determinance() << std::endl;
}

int main() {
    // Ejecutamos las pruebas para el algoritmo Bubble Sort
    test_bubble_sort_complexity();
    return 0;
}
