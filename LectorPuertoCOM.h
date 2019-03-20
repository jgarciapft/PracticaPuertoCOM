#ifndef LECTORPUERTOCOM_H
#define LECTORPUERTOCOM_H

#include <fstream>
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
	 * Mensaje de error cuando los BCE de la trama de fichero recibida y calculada no coinciden
	 */
	static const char MSJ_ERROR_BCE_INVALIDO_FCH[];
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
	 * Flujo asociado al archivo de recepci�n
	 */
	fstream fFichero;
	/**
	 * �ndice de campo de la trama siguiente a leer
	 */
	int idxTrama;
	/**
	 * Autor del fichero de recepci�n
	 */
	string autorFchRecep;
	/**
	 * Ruta en la que almacenar el fichero de recepci�n
	 */
	string rutaFchRecep;
	/**
	 * Bandera para indicar si se est� en proceso de procesar una trama
	 */
	bool esTrama;
	/**
	 * Bandera para indicar si se est� en proceso de leer tramas de datos provenientes de la recepci�n de archivos
	 */
	bool recepFichero;
	/**
	 * Bandera para indicar si se ha inicializado correctamente el flujo asociado al fichero recibido y, por lo tanto,
	 * se puede empezar a escribir el fichero de recepci�n. Un valor igual a 1 indica que se ha le�do la ruta y un valor
	 * de 2 quiere decir que se ha le�do tambi�n el autor.
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
	 * @return si el manejador del puerto COM est� inicializado
	 */
	bool manPrtoCOMAbierto();

	/**
	 * Comprueba si hay alg�n elemento en el buffer de lectura, y si lo hay lo devuelve
	 *
	 * @return Caracter le�do si existe, 0 si no se ha le�do nada
	 */
	char hayContenido();

	/**
	 * M�todo modificador del atributo 'idxTrama'
	 */
	void setIdxTrama(/* Nuevo valor del �ndice */int idxTrama);

	/**
	 * M�todo modificador del atributo 'esTrama'
	 */
	void setEsTrama(/* Nuevo valor de la bandera*/bool esTrama);

	/**
	 * M�todo modificador del atributo 'recepFichero'.
	 * Cierra el flujo asociado al fichero de recepci�n si la bandera es FALSO
	 */
	void setRecepFichero(/* Nuevo valor de la bandera*/bool recepFichero);

	/**
	 * M�todo modificador del atributo 'autorFichero'
	 */
	void setAutorFchRecep(/* Nuevo valor del autor*/const string &autorFchRecep);

	/**
	 * M�todo modificador del atributo 'rutaFchRecep'
	 */
	void setRutaFchRecep(/* Nuevo valor de la ruta*/const string &rutaFchRecep);

	/**
	 * M�todo modificador del atributo 'ficheroConfigurado'.
	 * Abre el flujo asociado al fichero de recepci�n si se est� recibiendd un fichero y la bandera es VERDADERO,
	 * entonces coge el valor del atributo 'rutaFchRecep' como ruta
	 */
	void setFicheroConfigurado(/* Nuevo valor de la bandera*/int ficheroConfigurado);

	/**
	 * @return Si se han le�do los par�metros necesarios para abrir el fichero de recepci�n
	 */
	bool ficheroEstaConfigurado();

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

	/**
	 * M�todo accesor del atributo 'esTrama'
	 */
	bool getEsTrama();

	/**
	 * M�todo accesor del atributo 'autorFichero'
	 */
	string getAutorFchRecep() const;

	/**
	 * M�todo accesor del atributo 'rutaFchRecep'
	 */
	string getRutaFchRecep() const;

	/**
	 * M�todo accesor del atributo 'recepFichero'
	 */
	bool getRecepFichero();

	/**
	 * M�todo accesor del atributo 'ficheroConfigurado'
	 */
	int getFicheroConfigurado();
};

#endif
