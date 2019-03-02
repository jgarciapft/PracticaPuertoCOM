#ifndef ESCRITORPUERTOCOM_H
#define ESCRITORPUERTOCOM_H

#include "ManejadorPuertoCOM.h"
#include "ManejadorEntradaUsuario.h"
#include "Principal.h"

/**
 * Manejador responsable de la escritura sobre el puerto COM
 * 
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
class EscritorPuertoCOM {

private:
	/**
	 * Manejador del puerto COM
	 */
	ManejadorPuertoCOM *mPuertoCOM;
	/**
	 * Bandera que indica si se ha leido el caracter de finalizaci�n del programa
	 */
	bool finCaracter;

	/**
	 * Comprueba si el manejador del puerto COM est� inicializado
	 */
	bool manPrtoCOMAbierto();

	/**
	 * M�todo modificador del atributo 'finCaracter'
	 */
	void setFinCaracter(/* Nuevo valor de la bandera */bool finCaracter);

public:
	EscritorPuertoCOM();

	explicit EscritorPuertoCOM(ManejadorPuertoCOM *mPuertoCOM);

	/**
	 * Maneja la funci�n de escritura del puerto COM. Maneja los casos de elecci�n de fin del programa, enviar mensaje, borrado de caracter y escritura de caracter
	 */
	void escritura();

	/**
	 * M�todo accesor del atributo 'finCaracter'
	 */
	bool getFinCaracter();
};

#endif
