# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(Practica1 VERSION 3.0)

# Especificar el estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluir los archivos fuente
add_executable(Practica1 
    main.cpp 
    funciones.cpp 
    ClaseTiempo.cpp 
    sistemaEcuaciones.cpp
)

# Enlace de librerías requeridas para tiempos en Linux (rt)
target_link_libraries(Practica1 rt)
