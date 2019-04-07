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
        TramaDatos.cpp
        Protocolo.cpp
        Protocolo.h
        ProtocoloEstandar.cpp
        ProtocoloEstandar.h
        CONSTANTES.cpp
        CONSTANTES.h
        CONSTANTES.cpp
        ManejadorProtocolo.cpp
        ManejadorProtocolo.h
        EscritorPuertoCOM_P_ME.cpp
        EscritorPuertoCOM_P_ME.h)
