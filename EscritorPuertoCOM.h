#ifndef ESCRITORPUERTOCOM_H
#define ESCRITORPUERTOCOM_H

#include <vector>
#include <fstream>
#include <algorithm>
#include "ManejadorPuertoCOM.h"
#include "CONSTANTES.h"
#include "TramaDatos.h"
#include "Trama.h"
#include "ManejadorInfoUsuario.h"
#include "LectorPuertoCOM.h"
#include "NumeroCiclico.h"

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
	 * Ruta por defecto del fichero fuente enviado por el puerto COM mediante el protocolo maestro-esclavo
	 */
	static const char RUTA_DEF_FICHERO_ENVIO_ME[];
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
	 * Configura la identidad de cada estación de trabajo (maestro o esclavo) y, para el maestro, elige la operación a
	 * realizar. Para configurar correctamente el protocolo primero se debe establecer un esclavo a la espera de que una
	 * estación maestra le indique la operación a realizar. Después devuelve el control al protocolo estándar
	 */
	void configurarProtocMaestroEsclavo();

	/**
	 * Operación de sonde por parte del maestro. Envía al esclavo el fichero indicado por la ruta
	 * RUTA_DEF_FICHERO_ENVIO_ME. El maestro termina la comunicación al finalizar el envío del fichero
	 */
	void maestro_seleccion();

	/**
	 * Operación de sondeo por parte del maestro. Hace que el esclavo le envíe el fichero indicado por la ruta
	 * RUTA_DEF_FICHERO_ENVIO_ME. Cuando el esclavo de indica que ha terminado de enviar el fichero es la voluntad
	 * del maestro la que indica al cierre preguntando al usuario si quiere cerrar la conexión o mantenerla abierta
	 */
	void maestro_sondeo();

	/**
	 * Fase de establecimiento común a ambas operaciones del esclavo. Espera a recibir una trama de control de la
	 * estación maestra que indique la operación a realizar
	 */
	void esclavo_establecimiento();

	/**
	 * Operación de selección por parte del esclavo. Recibe el fichero indicado por la ruta RUTA_DEF_FICHERO_ENVIO_ME
	 * del maestro. El maestro tiene la voluntad de cierre, el esclavo debe aceptarla forzosamente
	 */
	void esclavo_seleccion();

	/**
	 * Operación de sondeo por parte del esclavo. Envía el fichero indicado por la ruta RUTA_DEF_FICHERO_ENVIO_ME.
	 * La voluntad de cierre la tiene la estación maestra, el esclavo debe preguntar si puede cerrar la comunicación
	 * hasta que tenga la confirmación por parte del maestro
	 */
	void esclavo_sondeo();

	/**
	 * Espera a que el lector lea una trama completa
	 *
	 * @return Trama completa
	 */
	Trama *esperarTramaCompleta();

	/**
	 * Envía una trama de datos con confirmación mediante trama de control ACK del mismo campo de dirección y de
	 * número de trama
	 *
	 * @param tramaDatos Trama de datos a enviar
	 * @return Si se obtuvo la respuesta esperada
	 */
	boolean enviarTramaDatosConConfirmacion(TramaDatos tramaDatos);

	/**
	 * @return Trama de respuesta a la especificada por parámetro
	 */
	Trama elaborarRespuesta(Trama *pTrama);

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
	 * Formatea y envía el mensaje almacenado en el buffer de escritura por el puerto COM según el manejador
	 * establecido con confirmación
	 *
	 * @param buffer Buffer de caracteres con delimitador 0 del que formar las tramas
	 * @param d Campo de dirección de las tramas a enviar
	 * @param genNT Generador del campo de número de trama
	 */
	void enviarBufferTramasConConfirmacion(const char *buffer, unsigned char d, NumeroCiclico &genNT);

	/**
	 * Formatea el mensaje y divide el buffer de escritura en tramas para después enviarlas por el puerto COM
	 *
	 * @param buffer Buffer de caracteres con delimitador 0 del que formar las tramas
	 */
	void enviarBufferTramas(const char *buffer);

	/**
	 * Envia la trama de control especificada mostrando su resumen por consola
	 *
	 * @param tramaControl Trama de control a enviar
	 */
	void enviarTramaControlConResumen(Trama tramaControl);

	/**
	 * Formatea y envía una trama de control por el pueto COM según el manejador establecido
	 */
	void configuarTramaControl();

	/**
	 * Envía una trama de control por el puerto COM
	 */
	void enviarTramaControl(const Trama &tramaControl);

	/**
	 * Envía una trama de datos por el puerto COM
	 *
	 * @param tramaDatos Trama de datos a enviar
	 */
	void enviarTramaDatos(TramaDatos tramaDatos);

	/**
	 * Maneja el evío de un fichero por el puerto COM según el manejador establecido
	 */
	void enviarFichero(bool conConfirmacion, unsigned char dir);

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
	 * Maneja la funcin de escritura del puerto COM. Maneja los casos de elección de fin del programa, enviar mensaje,
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
