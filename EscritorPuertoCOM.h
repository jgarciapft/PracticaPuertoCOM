#ifndef ESCRITORPUERTOCOM_H
#define ESCRITORPUERTOCOM_H

#include <vector>
#include <fstream>
#include <algorithm>
#include "ManejadorPuertoCOM.h"
#include "CONSTANTES.h"
#include "TramaDatos.h"
#include "Trama.h"
#include "ManejadorEntradaUsuario.h"
#include "LectorPuertoCOM.h"

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
	/**
	 * Máxima longitud del campo de datos de una trama de datos
	 */
	static const int TD_MAX_LON_DATOS;

private:
	/**
	 * Instancia Singleton de la clase
	 */
	static EscritorPuertoCOM *instancia;
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
	 *
	 * @param bufferMsj Buffer de caracteres con delimitador 0 del que formar las tramas
	 */
	void enviarBufferTramas(const char *bufferMsj);

	/**
	 * Envía una trama de datos por el puerto COM
	 *
	 * @param tramaDatos Trama de datos a enviar
	 */
	void enviarTramaDatos(TramaDatos *tramaDatos);

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
	 *
	 * @param finCaracter Nuevo valor de la bandera
	 */
	void setFinCaracter(bool finCaracter);

	/**
	 * Método modificador del atributo 'idxBuffer'
	 *
	 * @param idxBuffer Nuevo valor del índice
	 */
	void setIdxBuffer(int idxBuffer);

public:

	EscritorPuertoCOM();

	~EscritorPuertoCOM();

	/**
	 * Maneja la función de escritura del puerto COM. Maneja los casos de elección de fin del programa, enviar mensaje,
	 * borrado de caracter y escritura de caracter
	 */
	void escritura();

	/**
	 * @return Instancia Singleton de la clase
	 */
	static EscritorPuertoCOM *recuperarInstancia();

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
