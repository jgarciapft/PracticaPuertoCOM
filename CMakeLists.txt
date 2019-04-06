cmake_minimum_required(VERSION 3.13)
project(PracticaPuertoCOM)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PracticaPuertoCOM
        PuertoSerie.cpp
        PuertoSerie.h
        CargadorManejadorPuertoCOM.cpp
        CargadorManejadorPuertoCOM.h
        EscritorPuertoCOM.cpp
        EscritorPuertoCOM.h
        LectorPuertoCOM.cpp
        LectorPuertoCOM.h
        ManejadorEntradaUsuario.cpp
        ManejadorEntradaUsuario.h
        ManejadorPuertoCOM.cpp
        ManejadorPuertoCOM.h
        Principal.cpp
        Principal.h
        Trama.cpp
        Trama.h
        TramaDatos.h
        TramaDatos.cpp Protocolo.cpp Protocolo.h ProtocoloEstandar.cpp ProtocoloEstandar.h)
