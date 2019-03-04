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
	static const unsigned char TC_DEF_DIRECCION;
	static const unsigned char TC_DEF_NT;

private:
	/**
	 * Máximo número base de caracteres en el buffer
	 */
	static const int BUFFER_MAX_CAR;
	/**
	 * Número de fines de linea al final del mensaje
	 */
	static const int MSJ_NUM_CRLF;
	/**
	 * Mensaje para mostrar las opciones de selección de tipo de trama de control
	 */
	static const char MSJ_SEL_TC[];
	/**
	 * Mensaje para indicar opción inválida en la elección de tipo de trama de control
	 */
	static const char MSJ_ERROR_SEL_TC[];

private:
	/**
	 * Manejador del puerto COM
	 */
	ManejadorPuertoCOM *mPuertoCOM;
	/**
	 * Índice de posición libre del buffer de escritura
	 */
	int idxBuffer;
	/**
	 * Bandera que indica si se ha leido el caracter de finalización del programa
	 */
	bool finCaracter;
	/**
	 * Buffer de escritura
	 */
	char *buffer;

	/**
	 * Comprueba si el manejador del puerto COM está inicializado
	 */
	bool manPrtoCOMAbierto();

	/**
	 * Comprueba si el buffer de escritura está lleno
	 */
	bool bufferLleno();

	/**
	 * Formatea y envía el mensaje almacenado en el buffer de escritura por el puerto COM según el manejador
	 * establecido
	 */
	void enviarMensaje();

	/**
	 * Formatea y envía una trama por el pueto COM según el manejador establecido
	 */
	void enviarTrama();

	/**
	 * Escribe en el buffer con 'echo' el caracter pasado
	 *
	 * @param car Caracter a tratar
	 */
	void leerCarEcho(char car);

	/**
	 * Método modificador del atributo 'finCaracter'
	 */
	void setFinCaracter(/* Nuevo valor de la bandera */bool finCaracter);

	/**
	 * Método modificador del atributo 'idxBuffer'
	 */
	void setIdxBuffer(/* Nuevo valor del índice */int idxBuffer);

public:

	EscritorPuertoCOM();

	explicit EscritorPuertoCOM(ManejadorPuertoCOM *mPuertoCOM);

	~EscritorPuertoCOM();

	/**
	 * Maneja la función de escritura del puerto COM. Maneja los casos de elección de fin del programa, enviar mensaje, borrado de caracter y escritura de caracter
	 */
	void escritura();

	/**
	 * Método accesor del atributo 'finCaracter'
	 */
	bool getFinCaracter();

	/**
	 * Método accesor del atributo 'idxBuffer'
	 */
	int getIdxBuffer();
};

#endif
