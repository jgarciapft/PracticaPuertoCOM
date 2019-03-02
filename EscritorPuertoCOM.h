#ifndef ESCRITORPUERTOCOM_H
#define ESCRITORPUERTOCOM_H

#include "ManejadorPuertoCOM.h"
#include "ManejadorEntradaUsuario.h"
#include "Principal.h"

/**
 * Manejador responsable de la escritura sobre el puerto COM
 * 
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
 */
class EscritorPuertoCOM {

private:
	/**
	 * Manejador del puerto COM
	 */
	ManejadorPuertoCOM *mPuertoCOM;
	/**
	 * Bandera que indica si se ha leido el caracter de finalización del programa
	 */
	bool finCaracter;

	/**
	 * Comprueba si el manejador del puerto COM está inicializado
	 */
	bool manPrtoCOMAbierto();

	/**
	 * Método modificador del atributo 'finCaracter'
	 */
	void setFinCaracter(/* Nuevo valor de la bandera */bool finCaracter);

public:
	EscritorPuertoCOM();

	explicit EscritorPuertoCOM(ManejadorPuertoCOM *mPuertoCOM);

	/**
	 * Maneja la función de escritura del puerto COM. Maneja los casos de elección de fin del programa, enviar mensaje, borrado de caracter y escritura de caracter
	 */
	void escritura();

	/**
	 * Método accesor del atributo 'finCaracter'
	 */
	bool getFinCaracter();
};

#endif
