#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include "CargadorManejadorPuertoCOM.h"

/**
 * Punto de entrada al programa. Controla el flujo de ejecuci�n y contiene la colecci�n de constantes comunes al programa
 * 
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */

class Principal {

public:
	/**
	 * Colecci�n de constantes de cadenas puerto COM
	 */
	static const LPCSTR COM[];
	/**
	 * Mensaje para mostrar las opciones de seleccionar un puerto COM
	 */
	static const char MSJ_SEL_COM[];
	/**
	 * Mensaje para indicar opci�n inv�lida en la elecci�n de puerto COM
	 */
	static const char MSJ_ERROR_SEL_COM[];
	/**
	 * Tasa de baudios por defecto
	 */
	static const DWORD VELOCIDAD_DEF;
	/**
	 * N�mero de bits por byte enviado / recibido por defecto
	 */
	static const BYTE NUM_BITS_X_BYTE_DEF;
	/**
	 * Configuraci�n de paridad por defecto
	 */
	static const BYTE PARIDAD_DEF;
	/**
	 * Configuraci�n de bits de stop por defecto
	 */
	static const BYTE BITS_STOP_DEF;
};

#endif
