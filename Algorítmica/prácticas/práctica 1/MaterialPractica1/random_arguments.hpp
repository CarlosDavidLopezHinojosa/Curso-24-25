#include <iostream>
#include <vector>
#include <random>
#include <type_traits>

    template<typename T>
    typename std::enable_if<std::is_arithmetic<T>::value, T>::type generate_random_value()
    {
        // Genera un valor aleatorio para tipos numéricos (int, float, double, etc.)
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1.0, 100.0); // Ajustar el rango según sea necesario
        return static_cast<T>(dis(gen));
    }

    // Sobrecarga para std::vector
    template<typename T>
    std::vector<T> generate_random_value()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1.0, 100.0);
        
        int size = static_cast<int>(dis(gen) / 10); // Ajustar tamaño según sea necesario
        std::vector<T> vec(size);
        for (auto& elem : vec)
        {
            elem = generate_random_value<typename std::decay<T>::type>(); // Recursivo
        }
        return vec;
    }

    template <typename T>
    std::vector<std::vector<T>> generate_random_value() 
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> size_dis(2, 10); // Tamaño aleatorio entre 2 y 10
        int outer_size = size_dis(gen);

        std::vector<std::vector<T>> vec(outer_size);
        for (auto& inner_vec : vec) 
        {
            inner_vec = generate_random_value<T>(); // Genera un std::vector<T>
        }
        return vec;
    }
