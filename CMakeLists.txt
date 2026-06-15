cmake_minimum_required(VERSION 3.20)
project(Tarea2_Arboles CXX)

# Usar el estándar C++23 como pide tu Makefile
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra")

# Decirle a CLion dónde están los .hpp
include_directories(include)

# Compilar el AVL como una librería interna
add_library(Arboles src/arboles/avl.cpp)

# Declarar todos tus ejecutables
add_executable(crear_datasets src/experimentos/base/crear_datasets.cpp)
add_executable(ia_bu src/experimentos/base/ia_bu.cpp)
add_executable(ia_bs src/experimentos/base/ia_bs.cpp)
add_executable(io_bu src/experimentos/base/io_bu.cpp)
add_executable(io_bs src/experimentos/base/io_bs.cpp)
add_executable(sat src/experimentos/teoremas/sat.cpp)
add_executable(wst src/experimentos/teoremas/wst.cpp)

# Enlazar el AVL a los experimentos (el creador de datasets no lo necesita)
target_link_libraries(ia_bu Arboles)
target_link_libraries(ia_bs Arboles)
target_link_libraries(io_bu Arboles)
target_link_libraries(io_bs Arboles)
target_link_libraries(sat Arboles)
target_link_libraries(wst Arboles)