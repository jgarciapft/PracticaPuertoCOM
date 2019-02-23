cmake_minimum_required(VERSION 3.13)
project(PracticaPuertoCOM)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PracticaPuertoCOM
        Sesion1.cpp
        PuertoSerie.cpp
        PuertoSerie.h)
