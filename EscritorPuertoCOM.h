#ifndef ESCRITORPUERTOCOM_H
#define ESCRITORPUERTOCOM_H


#include "ManejadorPuertoCOM.h"
#include "ManejadorEntradaUsuario.h"
#include "Principal.h"
#include "TramaDatos.h"

/**
 * Manejador responsable de la escritura sobre el puerto COM
 * 
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
 */
class EscritorPuertoCOM {

private:
	/**
	 * Valor por defecto del campo de dirección para tramas de control
	 */
	static const unsigned char TC_DEF_DIRECCION;
	/**
	 * Valor por defecto del campo de número de trama para tramas de control
	 */
	static const unsigned char TC_DEF_NT;
	/**
	 * Valor por defecto del campo deirección para tramas de datos
	 */
	static const unsigned char TD_DEF_DIRECCION;
	/**
	 * Valor por defecto del campo de control para tramas de datos
	 */
	static const unsigned char TD_DEF_CONTROL;
	/**
	 * Valor por defecto del campo de número de trama para tramas de datos
	 */
	static const unsigned char TD_DEF_NT;
	/**
	 * Mensaje de error que mostrar al usuario si no se ha podido abrir el fichero de envío
	 */
	static const char MSJ_ERR_FICHERO_ENVIO_NO_ENCONTRADO[];
	/**
	 * Mensaje que envía el emisor del fichero para indicar el comienzo del envío de un fichero
	 */
	static const char MSJ_INICIO_ENV_FICHERO[];
	/**
	 * Mensaje que envía el emisor del fichero para indicar el fin del envío de un fichero
	 */
	static const char MSJ_FIN_ENV_FICHERO[];
	/**
	 * Ruta por defecto del fichero fuente enviado por el puerto COM
	 */
	static const char RUTA_DEF_FICHERO_ENVIO[];

public:
	/**
	 * Caracter indicador del inicio del envío de un fichero
	 */
	static const char CHAR_INICIO_FICHERO = '#';
	/**
	 * Caracter indicador del fin del envío de un fichero
	 */
	static const char CHAR_FIN_FICHERO = '@';

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
	 * Formatea el mensaje y divide el buffer de escritura en tramas para después enviarlas por el puerto COM
	 */
	void enviarBufferTramas();

	/**
	 * Envía una trama de datos por el puerto COM
	 *
	 * @param tramaDatos Trama de datos a enviar
	 */
	void enviarTramaDatos(TramaDatos tramaDatos);

	/**
	 * Formatea y envía una trama de control por el pueto COM según el manejador establecido
	 */
	void enviarTramaControl();

	/**
	 * Maneja el evío de un fichero por el puerto COM según el manejador establecido
	 */
	void enviarFichero();

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
