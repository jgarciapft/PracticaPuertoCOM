#ifndef LECTORPUERTOCOM_H
#define LECTORPUERTOCOM_H

#include "ManejadorPuertoCOM.h"
#include "Trama.h"
#include "Principal.h"

/**
 * Manejador responsable de la lectura sobre el puertoCOM
 * 
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
class LectorPuertoCOM {

private:
	/**
	 * Mensaje de error cuando los BCE de la trama recibida y calculada no coinciden
	 */
	static const char MSJ_ERROR_BCE_INVALIDO[];
	/**
	 * Mensaje de inicio de recepci�n de fichero por parte del receptor
	 */
	static const char MSJ_INICIO_REC_FICHERO[];
	/**
	 * Mensaje de fin de recepci�n de fichero por parte del receptor
	 */
	static const char MSJ_FIN_REC_FICHERO[];

private:
	/**
	 * Manejador del puerto COM del que leer
	 */
	ManejadorPuertoCOM *mPuertoCOM;
	/**
	 * �ndice de campo de la trama siguiente a leer
	 */
	int idxTrama;
	/**
	 * Auxiliar sobre la que construir una trama
	 */
	Trama *tramaAux;

	/**
	 * Comprueba si el manejador del puerto COM est� inicializado
	 */
	bool manPrtoCOMAbierto();

	/**
	 * Comprueba si hay alg�n elemento en el buffer de lectura, y si lo hay lo devuelve
	 */
	char hayContenido();

	/**
	 * Maneja el procesamiento de un caracter
	 *
	 * @param car Caracter recibido
	 */
	void procesarCar(char car);

	/**
	 * M�todo modificador del atributo 'idxTrama'
	 */
	void setIdxTrama(/* Nuevo valor del �ndice */int idxTrama);

public:

	LectorPuertoCOM();

	explicit LectorPuertoCOM(ManejadorPuertoCOM *mPuertoCOM);

	/**
	 * Maneja la funci�n de lectura del puerto COM. Maneja la lectura de un caracter y la lectura de una trama
	 */
	void lectura();

	/**
	 * M�todo accesor del atributo 'idxTrama'
	 */
	int getIdxTrama();
};

#endif
