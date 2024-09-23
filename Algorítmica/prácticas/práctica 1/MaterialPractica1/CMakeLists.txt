cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(Practica1)

# Establecer el estándar de C++ a usar
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Opciones adicionales de compilación
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# Mensajes al usuario
message(STATUS "Compilando con C++ estándar 17 y usando ${CMAKE_CXX_FLAGS}")

# Archivos de cabecera comunes
set(HEADERS
    algorithmics_utils.hpp
    algorithmics_utils_impl.hpp
    ClaseTiempo.hpp
)

# Incluir directorios de encabezados (ruta base del proyecto y Eigen)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(/usr/include/eigen3)  # Ruta de Eigen en el sistema

# Ejecutable para bubble_sort
add_executable(bubble_sort bubble_sort.cpp ${HEADERS})

# Añadir flags de compilación para bubble_sort (por ejemplo, librería rt)
target_link_libraries(bubble_sort rt)

# Ejecutable para matrix multiplication
add_executable(matrix_mult matrix_multiplication.cpp ${HEADERS})

# Añadir flags de compilación para matrix_mult
target_link_libraries(matrix_mult rt)
