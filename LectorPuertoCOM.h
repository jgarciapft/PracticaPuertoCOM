#ifndef LECTORPUERTOCOM_H
#define LECTORPUERTOCOM_H

#include "ManejadorPuertoCOM.h"
#include "Trama.h"

/**
 * Manejador responsable de la lectura sobre el puertoCOM
 * 
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
class LectorPuertoCOM {

private:
	/**
	 * Manejador del puerto COM del que leer
	 */
	ManejadorPuertoCOM *mPuertoCOM;
	/**
	 * Bandera que indica si se est� leyendo una trama
	 */
	bool esTrama;
	/**
	 * Bandera que indica si se ha terminado de leer la trama en progreso de env�o
	 */
	bool finTrama;
	/**
	 * �ndice de campo de la trama siguiente a leer
	 */
	int idxTrama;
	/**
	 * Auxiliar sobre la que construir una trama
	 */
	Trama tramaAux;

	/**
	 * Comprueba si el manejador del puerto COM est� inicializado
	 */
	bool manPrtoCOMAbierto();

	/**
	 * Comprueba si hay alg�n elemento en el buffer de lectura, y si lo hay lo devuelve
	 */
	char hayContenido();

	/**
	 * M�todo modificador del atributo 'esTrama'
	 */
	void setEsTrama(/* Nuevo valor de la bandera */bool esTrama);

	/**
	 * M�todo modificador del atributo 'finTrama'
	 */
	void setFinTrama(/* Nuevo valor de la bandera */bool finTrama);

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
	 * M�todo accesor del atributo 'esTrama'
	 */
	bool getEsTrama();

	/**
	 * M�todo accesor del atributo 'finTrama'
	 */
	bool getFinTrama();

	/**
	 * M�todo accesor del atributo 'idxTrama'
	 */
	int getIdxTrama();

	/**
	 * M�todo accesor del atributo 'tramaAux'
	 */
	Trama getTramaAux();
};

#endif
