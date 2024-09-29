# Versión mínima de CMake
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(Practica1 CXX)

# Establecemos el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluimos los directorios con los archivos de cabecera
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/OrdenacionBurbuja
    ${CMAKE_SOURCE_DIR}/MultplicaciondeMatrices
    ${CMAKE_SOURCE_DIR}/DeterminanteRecursivo
)

# Agregamos los archivos comunes
set(COMMON_SOURCES
    common.cpp
    sistemaEcuaciones.cpp
)

# Ejecutable para el algoritmo de burbuja
add_executable(burbuja
    OrdenacionBurbuja/burbuja.cpp
    OrdenacionBurbuja/OrdenacionBurbuja.cpp
    ${COMMON_SOURCES}
)

# Ejecutable para la multiplicación de matrices
add_executable(matrix_mult
    MultplicaciondeMatrices/matrix_mult.cpp
    MultplicaciondeMatrices/MultiplicacionMatriz.cpp
    ${COMMON_SOURCES}
)

add_executable(det
    DeterminanteRecursivo/det.cpp
    DeterminanteRecursivo/DeterminanteRecursivo.cpp
    ${COMMON_SOURCES}
)
# Opcional: enlazamos librerías externas si es necesario (e.g., gnuplot, math)
# find_package(Gnuplot REQUIRED)
# target_link_libraries(burbuja Gnuplot::Gnuplot)
# target_link_libraries(matrix_mult Gnuplot::Gnuplot)
