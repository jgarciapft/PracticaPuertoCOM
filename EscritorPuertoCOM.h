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

	void configurarProtocMaestroEsclavo();

	void maestro_seleccion();

	void maestro_sondeo();

	void esclavo_establecimiento();

	void esclavo_seleccion();

	void esclavo_sondeo();

	Trama *esperarTramaCompleta();

	boolean enviarTramaDatosConfirmada(TramaDatos tramaDatos);

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

	void enviarBufferTramasConConfirmacion(const char *buffer, unsigned char d, NumeroCiclico &genNT);

	/**
	 * Formatea el mensaje y divide el buffer de escritura en tramas para despu�s enviarlas por el puerto COM
	 *
	 * @param buffer Buffer de caracteres con delimitador 0 del que formar las tramas
	 */
	void enviarBufferTramas(const char *buffer);

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
	void enviarFichero();

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
