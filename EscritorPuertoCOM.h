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
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
class EscritorPuertoCOM {

private:
	/**
	 * Valor por defecto del campo de direcci�n para tramas de control
	 */
	static const unsigned char TC_DEF_DIRECCION;
	/**
	 * Valor por defecto del campo de n�mero de trama para tramas de control
	 */
	static const unsigned char TC_DEF_NT;
	/**
	 * Valor por defecto del campo deirecci�n para tramas de datos
	 */
	static const unsigned char TD_DEF_DIRECCION;
	/**
	 * Valor por defecto del campo de control para tramas de datos
	 */
	static const unsigned char TD_DEF_CONTROL;
	/**
	 * Valor por defecto del campo de n�mero de trama para tramas de datos
	 */
	static const unsigned char TD_DEF_NT;
	/**
	 * Mensaje de error que mostrar al usuario si no se ha podido abrir el fichero de env�o
	 */
	static const char MSJ_ERR_FICHERO_ENVIO_NO_ENCONTRADO[];
	/**
	 * Mensaje que env�a el emisor del fichero para indicar el comienzo del env�o de un fichero
	 */
	static const char MSJ_INICIO_ENV_FICHERO[];
	/**
	 * Mensaje que env�a el emisor del fichero para indicar el fin del env�o de un fichero
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
	/**
	 * M�xima longitud del campo de datos de una trama de datos
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
	 * Configura la identidad de cada estaci�n de trabajo (maestro o esclavo) y, para el maestro, elige la operaci�n a
	 * realizar. Para configurar correctamente el protocolo primero se debe establecer un esclavo a la espera de que una
	 * estaci�n maestra le indique la operaci�n a realizar. Despu�s devuelve el control al protocolo est�ndar
	 */
	void configurarProtocMaestroEsclavo();

	/**
	 * Operaci�n de sonde por parte del maestro. Env�a al esclavo el fichero indicado por la ruta
	 * RUTA_DEF_FICHERO_ENVIO_ME. El maestro termina la comunicaci�n al finalizar el env�o del fichero
	 */
	void maestro_seleccion();

	/**
	 * Operaci�n de sondeo por parte del maestro. Hace que el esclavo le env�e el fichero indicado por la ruta
	 * RUTA_DEF_FICHERO_ENVIO_ME. Cuando el esclavo de indica que ha terminado de enviar el fichero es la voluntad
	 * del maestro la que indica al cierre preguntando al usuario si quiere cerrar la conexi�n o mantenerla abierta
	 */
	void maestro_sondeo();

	/**
	 * Fase de establecimiento com�n a ambas operaciones del esclavo. Espera a recibir una trama de control de la
	 * estaci�n maestra que indique la operaci�n a realizar
	 */
	void esclavo_establecimiento();

	/**
	 * Operaci�n de selecci�n por parte del esclavo. Recibe el fichero indicado por la ruta RUTA_DEF_FICHERO_ENVIO_ME
	 * del maestro. El maestro tiene la voluntad de cierre, el esclavo debe aceptarla forzosamente
	 */
	void esclavo_seleccion();

	/**
	 * Operaci�n de sondeo por parte del esclavo. Env�a el fichero indicado por la ruta RUTA_DEF_FICHERO_ENVIO_ME.
	 * La voluntad de cierre la tiene la estaci�n maestra, el esclavo debe preguntar si puede cerrar la comunicaci�n
	 * hasta que tenga la confirmaci�n por parte del maestro
	 */
	void esclavo_sondeo();

	/**
	 * Espera a que el lector lea una trama completa
	 *
	 * @return Trama completa
	 */
	Trama *esperarTramaCompleta();

	/**
	 * Env�a una trama de datos con confirmaci�n mediante trama de control ACK del mismo campo de direcci�n y de
	 * n�mero de trama
	 *
	 * @param tramaDatos Trama de datos a enviar
	 * @return Si se obtuvo la respuesta esperada
	 */
	boolean enviarTramaDatosConConfirmacion(TramaDatos tramaDatos);

	/**
	 * @return Trama de respuesta a la especificada por par�metro
	 */
	Trama elaborarRespuesta(Trama *pTrama);

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
	 * Formatea y env�a el mensaje almacenado en el buffer de escritura por el puerto COM seg�n el manejador
	 * establecido con confirmaci�n
	 *
	 * @param buffer Buffer de caracteres con delimitador 0 del que formar las tramas
	 * @param d Campo de direcci�n de las tramas a enviar
	 * @param genNT Generador del campo de n�mero de trama
	 */
	void enviarBufferTramasConConfirmacion(const char *buffer, unsigned char d, NumeroCiclico &genNT);

	/**
	 * Formatea el mensaje y divide el buffer de escritura en tramas para despu�s enviarlas por el puerto COM
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
	 * Formatea y env�a una trama de control por el pueto COM seg�n el manejador establecido
	 */
	void configuarTramaControl();

	/**
	 * Env�a una trama de control por el puerto COM
	 */
	void enviarTramaControl(const Trama &tramaControl);

	/**
	 * Env�a una trama de datos por el puerto COM
	 *
	 * @param tramaDatos Trama de datos a enviar
	 */
	void enviarTramaDatos(TramaDatos tramaDatos);

	/**
	 * Maneja el ev�o de un fichero por el puerto COM seg�n el manejador establecido
	 */
	void enviarFichero(bool conConfirmacion, unsigned char dir);

	/**
	 * Escribe en el buffer con 'echo' el caracter pasado
	 *
	 * @param car Caracter a tratar
	 */
	void leerCarEcho(char car);

	/**
	 * M�todo modificador del atributo 'finCaracter'
	 *
	 * @param finCaracter Nuevo valor de la bandera
	 */
	void setFinCaracter(bool finCaracter);

	/**
	 * M�todo modificador del atributo 'idxBuffer'
	 *
	 * @param idxBuffer Nuevo valor del �ndice
	 */
	void setIdxBuffer(int idxBuffer);

public:

	EscritorPuertoCOM();

	~EscritorPuertoCOM();

	/**
	 * Maneja la funcin de escritura del puerto COM. Maneja los casos de elecci�n de fin del programa, enviar mensaje,
	 * borrado de caracter y escritura de caracter
	 */
	void escritura();

	/**
	 * @return Instancia Singleton de la clase
	 */
	static EscritorPuertoCOM *recuperarInstancia();

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
