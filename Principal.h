#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include "ManejadorPuertoCOM.h"
#include "ManejadorEntradaUsuario.h"
#include "CargadorManejadorPuertoCOM.h"
#include "LectorPuertoCOM.h"
#include "EscritorPuertoCOM.h"

/**
 * Punto de entrada al programa. Controla el flujo de ejecuci�n y contiene la colecci�n de constantes comunes al programa
 * 
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */

class CONSTANTES {

public:
	/**
	 * Tipo enumerado de c�digos ASCII �tiles para el programa
	 */
	enum COD_ASCII {
		ESCAPE = 27,
		SINCRONISMO = 22,
		TECLA_FUNCION = '\0',
		TECLA_F1 = 59,
		TECLA_F2 = 60,
		TECLA_F3 = 61,
		TECLA_RETROCESO = '\b',
		TECLA_RETORNO = 13,
		CRLN = '\n',
		DELIM_CAD = '\0'
	};

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
