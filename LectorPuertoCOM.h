#ifndef LECTORPUERTOCOM_H
#define LECTORPUERTOCOM_H

#include "ManejadorPuertoCOM.h"
#include "Trama.h"

/**
 * Manejador responsable de la lectura sobre el puertoCOM
 * 
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
 */
class LectorPuertoCOM {

private:
	/**
	 * Manejador del puerto COM del que leer
	 */
	ManejadorPuertoCOM *mPuertoCOM;
	/**
	 * Bandera que indica si se está leyendo una trama
	 */
	bool esTrama;
	/**
	 * Bandera que indica si se ha terminado de leer la trama en progreso de envío
	 */
	bool finTrama;
	/**
	 * ïndice de campo de la trama siguiente a leer
	 */
	int idxTrama;
	/**
	 * Auxiliar sobre la que construir una trama
	 */
	Trama tramaAux;

	/**
	 * Método modificador del atributo 'esTrama'
	 */
	void setEsTrama(/* Nuevo valor de la bandera */bool esTrama);

	/**
	 * Método modificador del atributo 'finTrama'
	 */
	void setFinTrama(/* Nuevo valor de la bandera */bool finTrama);

	/**
	 * Método modificador del atributo 'idxTrama'
	 */
	void setIdxTrama(/* Nuevo valor del índice */int idxTrama);

public:
	LectorPuertoCOM();

	LectorPuertoCOM(ManejadorPuertoCOM mPuertoCOM);

	/**
	 * Maneja la función de lectura del puerto COM. Maneja la lectura de un caracter y la lectura de una trama
	 */
	char lectura();

	/**
	 * Método accesor del atributo 'esTrama'
	 */
	bool getEsTrama();

	/**
	 * Método accesor del atributo 'finTrama'
	 */
	bool getFinTrama();

	/**
	 * Método accesor del atributo 'idxTrama'
	 */
	int getIdxTrama();

	/**
	 * Método accesor del atributo 'tramaAux'
	 */
	Trama getTramaAux();
};

#endif
