cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(Practica1)

# Establecer el estándar de C++ a usar
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluir directorios de encabezados
include_directories(${CMAKE_SOURCE_DIR})
include_directories(/usr/include/eigen3) 

# Archivos fuente
set(SOURCES
    main.cpp
)

# Archivos de cabecera adicionales
set(HEADERS
    algorithmics_utils.hpp
    algorithmics_utils_impl.hpp
    ClaseTiempo.hpp
)

# Añadir el ejecutable
add_executable(Practica1 ${SOURCES})

# Añadir flags de compilación (por ejemplo, para usar pthread o la librería rt para clock_gettime)
target_link_libraries(Practica1 rt)

# Opciones adicionales de compilación
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# Mensajes al usuario
message(STATUS "Compilando con C++ estándar 17 y usando ${CMAKE_CXX_FLAGS}")
