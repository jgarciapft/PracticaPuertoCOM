#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include "CargadorManejadorPuertoCOM.h"

/**
 * Punto de entrada al programa. Controla el flujo de ejecución y contiene la colección de constantes comunes al programa
 * 
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
 */

class Principal {

public:
	/**
	 * Colección de constantes de cadenas puerto COM
	 */
	static const LPCSTR COM[];
	/**
	 * Mensaje para mostrar las opciones de seleccionar un puerto COM
	 */
	static const char MSJ_SEL_COM[];
	/**
	 * Mensaje para indicar opción inválida en la elección de puerto COM
	 */
	static const char MSJ_ERROR_SEL_COM[];
	/**
	 * Tasa de baudios por defecto
	 */
	static const DWORD VELOCIDAD_DEF;
	/**
	 * Número de bits por byte enviado / recibido por defecto
	 */
	static const BYTE NUM_BITS_X_BYTE_DEF;
	/**
	 * Configuración de paridad por defecto
	 */
	static const BYTE PARIDAD_DEF;
	/**
	 * Configuración de bits de stop por defecto
	 */
	static const BYTE BITS_STOP_DEF;
};

#endif
