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
	static const unsigned char TC_DEF_DIRECCION;
	static const unsigned char TC_DEF_NT;

private:
	/**
	 * M�ximo n�mero base de caracteres en el buffer
	 */
	static const int BUFFER_MAX_CAR;
	/**
	 * N�mero de fines de linea al final del mensaje
	 */
	static const int MSJ_NUM_CRLF;
	/**
	 * Mensaje para mostrar las opciones de selecci�n de tipo de trama de control
	 */
	static const char MSJ_SEL_TC[];
	/**
	 * Mensaje para indicar opci�n inv�lida en la elecci�n de tipo de trama de control
	 */
	static const char MSJ_ERROR_SEL_TC[];

private:
	/**
	 * Manejador del puerto COM
	 */
	ManejadorPuertoCOM *mPuertoCOM;
	/**
	 * �ndice de posici�n libre del buffer de escritura
	 */
	int idxBuffer;
	/**
	 * Bandera que indica si se ha leido el caracter de finalizaci�n del programa
	 */
	bool finCaracter;
	/**
	 * Buffer de escritura
	 */
	char *buffer;

	/**
	 * Comprueba si el manejador del puerto COM est� inicializado
	 */
	bool manPrtoCOMAbierto();

	/**
	 * Comprueba si el buffer de escritura est� lleno
	 */
	bool bufferLleno();

	/**
	 * Formatea y env�a el mensaje almacenado en el buffer de escritura por el puerto COM seg�n el manejador
	 * establecido
	 */
	void enviarMensaje();

	/**
	 * Formatea y env�a una trama por el pueto COM seg�n el manejador establecido
	 */
	void enviarTrama();

	/**
	 * Escribe en el buffer con 'echo' el caracter pasado
	 *
	 * @param car Caracter a tratar
	 */
	void leerCarEcho(char car);

	/**
	 * M�todo modificador del atributo 'finCaracter'
	 */
	void setFinCaracter(/* Nuevo valor de la bandera */bool finCaracter);

	/**
	 * M�todo modificador del atributo 'idxBuffer'
	 */
	void setIdxBuffer(/* Nuevo valor del �ndice */int idxBuffer);

public:

	EscritorPuertoCOM();

	explicit EscritorPuertoCOM(ManejadorPuertoCOM *mPuertoCOM);

	~EscritorPuertoCOM();

	/**
	 * Maneja la funci�n de escritura del puerto COM. Maneja los casos de elecci�n de fin del programa, enviar mensaje, borrado de caracter y escritura de caracter
	 */
	void escritura();

	/**
	 * M�todo accesor del atributo 'finCaracter'
	 */
	bool getFinCaracter();

	/**
	 * M�todo accesor del atributo 'idxBuffer'
	 */
	int getIdxBuffer();
};

#endif
