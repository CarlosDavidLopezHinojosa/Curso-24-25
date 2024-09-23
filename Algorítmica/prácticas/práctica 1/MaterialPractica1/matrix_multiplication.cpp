#include "algorithmics_utils.hpp"

// Función de multiplicación de matrices
void matrix_multiply(Eigen::MatrixXd& A, Eigen::MatrixXd& B, Eigen::MatrixXd& C) {
    C = A * B;  // Multiplicación de matrices
}

// Generador de matrices aleatorias
std::tuple<Eigen::MatrixXd&, Eigen::MatrixXd&, Eigen::MatrixXd&> generate_random_matrices(int size) {
    static Eigen::MatrixXd A(size, size);
    static Eigen::MatrixXd B(size, size);
    static Eigen::MatrixXd C(size, size);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 100.0); // Números aleatorios entre 0 y 100

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            A(i, j) = dist(gen);
            B(i, j) = dist(gen);
        }
    }

    return std::tie(A, B, C);
}

// Función para ejecutar las pruebas
void test_matrix_multiplication_complexity() {
    PolynomialComplexity<void, Eigen::MatrixXd, Eigen::MatrixXd, Eigen::MatrixXd> matrix_multiplication_complexity(
        matrix_multiply,
        generate_random_matrices,
        3 // Complejidad O(n^3) para multiplicación de matrices
    );

    int min_size = 100;    // Tamaño mínimo de las matrices (100x100)
    int max_size = 500;    // Tamaño máximo de las matrices (500x500)
    int iterations = 10;   // Número de iteraciones para la prueba

    // Calculamos la complejidad del algoritmo
    matrix_multiplication_complexity.calculate_complexity(min_size, max_size, iterations);

    // Calculamos las estadísticas
    matrix_multiplication_complexity.calculate_statistics();

    // Mostramos los resultados
    std::cout << "Matrix Multiplication Complexity Analysis:" << std::endl;
    std::cout << "Real Mean Time: " << matrix_multiplication_complexity.real_mean() << " microseconds" << std::endl;
    std::cout << "Calculated Mean Time: " << matrix_multiplication_complexity.calculated_mean() << " microseconds" << std::endl;
    std::cout << "Real Variance: " << matrix_multiplication_complexity.real_variance() << std::endl;
    std::cout << "Calculated Variance: " << matrix_multiplication_complexity.calculated_variance() << std::endl;
    std::cout << "Real Standard Deviation: " << matrix_multiplication_complexity.real_std_dev() << std::endl;
    std::cout << "Calculated Standard Deviation: " << matrix_multiplication_complexity.calculated_std_dev() << std::endl;
    std::cout << "Determination Coefficient: " << matrix_multiplication_complexity.determinance() << std::endl;
}

int main() {
    // Ejecutamos la prueba de la multiplicación de matrices
    test_matrix_multiplication_complexity();
    return 0;
}
