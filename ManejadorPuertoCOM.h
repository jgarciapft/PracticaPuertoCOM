#ifndef MANEJADORPUERTOCOM_H
#define MANEJADORPUERTOCOM_H

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include "PuertoSerie.h"

/**
 * Manejador de la instancia que gobierna las operaciones sobre el puerto COM. Sigue el patrón de diseño Singleton.
 * 
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
 */
class ManejadorPuertoCOM {

private:
	/**
	 * Instancia Singleton del manejador del puerto COM
	 */
	static ManejadorPuertoCOM *instancia;
	/**
	 * Manejador del puerto COM
	 */
	HANDLE handle;
	/**
	 * Bandera de estado que indica si el manejador está operativo
	 */
	bool estadoAbierto;

	/**
	 * Constructor privado para evitar su invocación exterior
	 */
	ManejadorPuertoCOM();

	/**
	 * Método modificador del atributo 'estadoAbierto'
	 *
	 * @param estadoAbierto Nuevo valor de la bandera de estado
	 */
	void setEstadoAbierto(boolean estadoAbierto);

public:
	/**
	 * Intenta abrir el manejador en el puerto COM deseado. Devuelve 'VERDADERO' si el manejador fue correctamente
	 * inicializado, 'FALSO' en otro caso
	 *
	 * @param nombrePuerto Constante que indica el puerto COM a elegir
	 * @param velocidad Tasa de baudios
	 * @param numBitsXByte Número de bits en cada byte enviado o recibido. Valor entre 4 y 8, ambos inclusive
	 * @param paridad Bit de paridad.
     *   0 = sin paridad
     *   1=impar
     *   2=par
     *   3=marca
     *   4=espacio
     * @param bitsParada Bits de stop.
     *   0 = 1 bit
     *   1 = 1.5 bits
     *   2 = 2 bits
	 */
	bool
	abrirManejador(LPCSTR nombrePuerto, DWORD velocidad, BYTE numBitsXByte, BYTE paridad, BYTE bitsParada);

	/**
	 * Cierra el manejador del puerto COM
	 */
	void cerrarManejador();

	/**
	 * Devuelve la instancia Singleton de la clase o 'nullptr' si no está operativa
	 */
	static ManejadorPuertoCOM *recuperarInstancia();

	/**
	 * Método accesor del atributo 'handle'
	 */
	HANDLE getHandle();

	/**
	 * Consulta el estado de la instancia Singleton del manejador del puerto COM
	 */
	bool getEstadoAbierto();
};

#endif
