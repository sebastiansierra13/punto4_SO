# CMake mínimo requerido
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(Punto4SO)

# Establecer el estándar de C++ (C++11 en este caso)
set(CMAKE_CXX_STANDARD 11)

# Incluir directorios de headers
include_directories(include)

# Añadir todos los archivos .cpp de la carpeta src
file(GLOB SOURCES "src/*.cpp")

# Crear el ejecutable a partir de los archivos fuente
add_executable(Punto4SO ${SOURCES})
