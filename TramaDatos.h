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
	char *datos;
	/**
	 * Bloque de control de errores
	 */
	unsigned char BCE;

	/**
	 * M�todo modificador del atributo 'L'
	 */
	void setL(/* Nuevo valor de la longitud */unsigned char L);

	/**
	 * M�todo modificador del atributo 'BCE'
	 */
	void setBCE(/* Nuevo valor del BCE */unsigned char BCE);

public:

	TramaDatos();

	TramaDatos(unsigned char S, unsigned char D, unsigned char C, unsigned char NT, unsigned char L,
			   char *datos);

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
	 * M�todo modificador global
	 */
	void
	setAttr(/* Nuevo valor del caracter de sincronismo */unsigned char S,/* Nuevo valor del caracter de direcci�n */
														 unsigned char D,/* Nuevo valor del caracter de control */
														 unsigned char C, /* Nuevo valor del n�mero de trama */
														 unsigned char NT,/* Nuevo valor de la longitud */
														 unsigned char L, /* Nuevo mensaje */char *datos);

	/**
	 * Devuelve la representaci�n en cadena de la trama de datos
	 */
	std::string toString() override;
};

#endif
