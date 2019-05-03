#ifndef TRAMADATOS_H
#define TRAMADATOS_H

#include "Trama.h"

/**
 * Clase que modela una trama de datos. Deriva de la clase Trama
 * 
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
class TramaDatos : public Trama {

private:
	/**
	 * Caracter de susituci�n del primer caracter de los datos para introducir un error en el BCE
	 */
	static const char CHAR_SUSTITUCION_ERROR_BCE;

private:

	/**
	 * Longitud del mensaje contenido en la trama
	 */
	unsigned char L;
	/**
	 * Mensaje contenido en la trama
	 */
	const char *datos;
	/**
	 * Bloque de control de errores
	 */
	unsigned char BCE;

public:

	TramaDatos();

	explicit TramaDatos(Trama *trama);

	TramaDatos(unsigned char S, unsigned char D, unsigned char C, unsigned char NT, unsigned char L,
			   const char *datos);

	/**
	 * Reemplaza el primer caracter de los datos con el caracter CHAR_SUSTITUCION_ERROR_BCE
	 *
	 * @return Caracter sustituido
	 */
	char sustituirPrimerCaracter();

	/**
	 * Reestaura el caracter de error introducido artificialmente para causar un error en el BCE
	 *
	 * @param charSustituido Caracter que fue sustituido y debe ser restaurado
	 */
	void restaurarPrimerCaracter(char charSustituido);

	/**
	 * @return Puntero a una copia de la instacia actual
	 */
	Trama *copia() override;

	/**
	 * Calcula y almacena el BCE para el mensaje contenido en la trama
	 */
	void calcularBCE();

	/**
	 * @param tramaDatos Trama de datos
	 * @return BCE correspondiente a la trama de datos
	 */
	static unsigned char calcularBCE(TramaDatos *tramaDatos);

	/**
	 * M�todo accesor del atributo 'L'
	 */
	unsigned char getL();

	/**
	 * M�todo accesor del atributo 'BCE'
	 */
	unsigned char getBCE();

	/**
	 * M�todo accesor del atributo 'datos'
	 */
	const char *getDatos();

	/**
	 * M�todo modificador del atributo 'L'
 	 *
 	 * @param L Nuevo valor de la longitud
	 */
	void setL(unsigned char L);

	/**
	 * M�todo modificador del atributo 'datos'
	 *
	 * @param datos Nuevo mensaje
	 */
	void setDatos(char *datos);

	/**
	 * M�todo modificador global
	 *
	 * @param S Nuevo valor del caracter de sincronismo
	 * @param D Nuevo valor del caracter de direcci�n
	 * @param C Nuevo valor del caracter de control
	 * @param NT Nuevo valor del n�mero de trama
	 * @param L Nuevo valor de la longitud
	 * @param datos Nuevo mensaje
	 */
	void
	setAttr(unsigned char S, unsigned char D, unsigned char C, unsigned char NT, unsigned char L, char *datos);

	/**
	 * @return Representaci�n en cadena de la trama
	 */
	std::string toString() override;

	/**
	 * @param BCECalculado BCE calculado externamente
	 * @return Representaci�n en formato especial para ser mostrado en el resumen de la comunicaci�n de protocolo,
	 * mostrando el BCE calculado externamente
	 */
	std::string protoc_toString(unsigned char BCECalculado);

	/**
	 * @return Representaci�n en formato especial para ser mostrado en el resumen de la comunicaci�n de protocolo
	 */
	std::string protoc_toString() override;


/**
 * M�todo modificador del atributo 'BCE'
 *
 * @param BCE Nuevo BCE
 */
void setBCE(unsigned char BCE);
};

#endif
