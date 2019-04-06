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

	/**
	 * M�todo modificador del atributo 'BCE'
	 *
	 * @param BCE Nuevo BCE
	 */
	void setBCE(unsigned char BCE);

public:

	/**
	 * TODO A�adir modo de protocolo
	 *
	 * @param nt N�mero de trama
	 * @param lon Longitud de los datos
	 * @param datos Datos a enviar
	 * @return Trama de datos formateada para trabajar con el protocolo Maestro-Esclavo
	 */
	static TramaDatos envioDatosN(unsigned char nt, unsigned char lon, const char *datos);

	TramaDatos();

	TramaDatos(unsigned char S, unsigned char D, unsigned char C, unsigned char NT, unsigned char L,
			   const char *datos);

	/**
	 * Calcula el BCE para el mensaje contenido en la trama
	 */
	void calcularBCE();

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
	 * Devuelve la representaci�n en cadena de la trama de datos
	 */
	std::string toString() override;
};

#endif
