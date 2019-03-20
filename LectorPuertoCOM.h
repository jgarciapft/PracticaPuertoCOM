#ifndef LECTORPUERTOCOM_H
#define LECTORPUERTOCOM_H

#include <fstream>
#include "ManejadorPuertoCOM.h"
#include "Trama.h"
#include "Principal.h"

/**
 * Manejador responsable de la lectura sobre el puertoCOM
 *
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
 */
class LectorPuertoCOM {

private:
	/**
	 * Mensaje de error cuando los BCE de la trama recibida y calculada no coinciden
	 */
	static const char MSJ_ERROR_BCE_INVALIDO[];
	/**
	 * Mensaje de error cuando los BCE de la trama de fichero recibida y calculada no coinciden
	 */
	static const char MSJ_ERROR_BCE_INVALIDO_FCH[];
	/**
	 * Mensaje de inicio de recepción de fichero por parte del receptor
	 */
	static const char MSJ_INICIO_REC_FICHERO[];
	/**
	 * Mensaje de fin de recepción de fichero por parte del receptor
	 */
	static const char MSJ_FIN_REC_FICHERO[];

private:
	/**
	 * Manejador del puerto COM del que leer
	 */
	ManejadorPuertoCOM *mPuertoCOM;
	/**
	 * Flujo asociado al archivo de recepción
	 */
	fstream fFichero;
	/**
	 * Índice de campo de la trama siguiente a leer
	 */
	int idxTrama;
	/**
	 * Autor del fichero de recepción
	 */
	string autorFchRecep;
	/**
	 * Ruta en la que almacenar el fichero de recepción
	 */
	string rutaFchRecep;
	/**
	 * Bandera para indicar si se está en proceso de procesar una trama
	 */
	bool esTrama;
	/**
	 * Bandera para indicar si se está en proceso de leer tramas de datos provenientes de la recepción de archivos
	 */
	bool recepFichero;
	/**
	 * Bandera para indicar si se ha inicializado correctamente el flujo asociado al fichero recibido y, por lo tanto,
	 * se puede empezar a escribir el fichero de recepción. Un valor igual a 1 indica que se ha leído la ruta y un valor
	 * de 2 quiere decir que se ha leído también el autor.
	 */
	int ficheroConfigurado;

	/**
	 * Auxiliar sobre la que construir una trama
	 */
	Trama *tramaAux;

	/**
	 * Maneja el procesamiento de un caracter
	 *
	 * @param car Caracter recibido
	 */
	void procesarCar(/* Caracter a procesar*/char car);

	/**
	 * Maneja el procesamiento de una trama
	 */
	void leerTrama(/* Caracter de trama*/char car);

	/**
	 * @return si el manejador del puerto COM está inicializado
	 */
	bool manPrtoCOMAbierto();

	/**
	 * Comprueba si hay algún elemento en el buffer de lectura, y si lo hay lo devuelve
	 *
	 * @return Caracter leído si existe, 0 si no se ha leído nada
	 */
	char hayContenido();

	/**
	 * Método modificador del atributo 'idxTrama'
	 */
	void setIdxTrama(/* Nuevo valor del índice */int idxTrama);

	/**
	 * Método modificador del atributo 'esTrama'
	 */
	void setEsTrama(/* Nuevo valor de la bandera*/bool esTrama);

	/**
	 * Método modificador del atributo 'recepFichero'.
	 * Cierra el flujo asociado al fichero de recepción si la bandera es FALSO
	 */
	void setRecepFichero(/* Nuevo valor de la bandera*/bool recepFichero);

	/**
	 * Método modificador del atributo 'autorFichero'
	 */
	void setAutorFchRecep(/* Nuevo valor del autor*/const string &autorFchRecep);

	/**
	 * Método modificador del atributo 'rutaFchRecep'
	 */
	void setRutaFchRecep(/* Nuevo valor de la ruta*/const string &rutaFchRecep);

	/**
	 * Método modificador del atributo 'ficheroConfigurado'.
	 * Abre el flujo asociado al fichero de recepción si se está recibiendd un fichero y la bandera es VERDADERO,
	 * entonces coge el valor del atributo 'rutaFchRecep' como ruta
	 */
	void setFicheroConfigurado(/* Nuevo valor de la bandera*/int ficheroConfigurado);

	/**
	 * @return Si se han leído los parámetros necesarios para abrir el fichero de recepción
	 */
	bool ficheroEstaConfigurado();

public:
	LectorPuertoCOM();

	explicit LectorPuertoCOM(ManejadorPuertoCOM *mPuertoCOM);

	/**
	 * Maneja la función de lectura del puerto COM. Maneja la lectura de un caracter y la lectura de una trama
	 */
	void lectura();

	/**
	 * Método accesor del atributo 'idxTrama'
	 */
	int getIdxTrama();

	/**
	 * Método accesor del atributo 'esTrama'
	 */
	bool getEsTrama();

	/**
	 * Método accesor del atributo 'autorFichero'
	 */
	string getAutorFchRecep() const;

	/**
	 * Método accesor del atributo 'rutaFchRecep'
	 */
	string getRutaFchRecep() const;

	/**
	 * Método accesor del atributo 'recepFichero'
	 */
	bool getRecepFichero();

	/**
	 * Método accesor del atributo 'ficheroConfigurado'
	 */
	int getFicheroConfigurado();
};

#endif
