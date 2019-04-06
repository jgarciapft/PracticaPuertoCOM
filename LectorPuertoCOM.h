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
	 * Instancia Singleton de la clase
	 */
	static LectorPuertoCOM *instancia;
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
	 * Auxiliar sobre la que construir una trama
	 */
	Trama *tramaAux;
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

	LectorPuertoCOM();

	/**
	 * Maneja el procesamiento de un caracter
	 *
	 * @param car Caracter recibido
	 */
	Trama *procesarCar(/* Caracter a procesar*/char car);

	/**
	 * Maneja el procesamiento de una trama
	 *
	 * @param car /Caracter de trama
	 */
	Trama* leerTrama(char car);

	/**
	 * Procesa la trama de datos recibida para buscar campos de la cabecera empleados para configurar el fichero
	 * de recepci�n: ruta relativa del fichero de recepci�n y autor del env�o. Los campos pueden incluirse en una trama,
	 * separados cada uno en una trama, o en varias si no caben. CUIDADO: Toda infromaci�n en una trama de
	 * datos que contiene campos de cabecera debe incluir �nicamente informaci�n sobre la cabecera, si incluye parte del
	 * cuerpo del mensaje ser� ignorado
	 */
	void procesarCabeceraFchRecep();

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
	 * @return Si se han le�do los par�metros necesarios para abrir el fichero de recepci�n
	 */
	bool ficheroEstaConfigurado();

	/**
	 * M�todo modificador del atributo 'idxTrama'
	 *
	 * @param idxTrama Nuevo valor del �ndice
	 */
	void setIdxTrama(int idxTrama);

	/**
	 * M�todo modificador del atributo 'esTrama'
	 *
	 * @param esTrama Nuevo valor de la bandera
	 */
	void setEsTrama(bool esTrama);

	/**
	 * M�todo modificador del atributo 'recepFichero'.
	 * Cierra el flujo asociado al fichero de recepci�n si la bandera es FALSO
	 *
	 * @param recepFichero Nuevo valor de la bandera
	 */
	void setRecepFichero(bool recepFichero);

	/**
	 * M�todo modificador del atributo 'autorFichero'
	 *
	 * @param autorFchRecep Nuevo valor del autor
	 */
	void setAutorFchRecep(const string &autorFchRecep);

	/**
	 * M�todo modificador del atributo 'rutaFchRecep'
	 *
	 * @param Nuevo valor de la ruta
	 */
	void setRutaFchRecep(const string &rutaFchRecep);

	/**
	 * M�todo modificador del atributo 'ficheroConfigurado'.
	 * Abre el flujo asociado al fichero de recepci�n si se est� recibiendd un fichero y la bandera es VERDADERO,
	 * entonces coge el valor del atributo 'rutaFchRecep' como ruta
	 *
	 * @param Nuevo valor de la bandera
	 */
	void setFicheroConfigurado(int ficheroConfigurado);

public:

	/**
	 * Maneja la funci�n de lectura del puerto COM. Maneja la lectura de un caracter y la lectura de una trama
	 */
	Trama *lectura();

	/**
	 * @return Instancia Singleton de la clase
	 */
	static LectorPuertoCOM *recuperarInstancia();

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
