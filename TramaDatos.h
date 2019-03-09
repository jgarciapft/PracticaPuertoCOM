#ifndef TRAMADATOS_H
#define TRAMADATOS_H

#include "Trama.h"

/**
 * Clase que modela una trama de datos. Deriva de la clase Trama
 * 
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
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
	 * Método modificador del atributo 'L'
	 */
	void setL(/* Nuevo valor de la longitud */unsigned char L);

	/**
	 * Método modificador del atributo 'BCE'
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
	 * Método accesor del atributo 'L'
	 */
	unsigned char getL();

	/**
	 * Método accesor del atributo 'BCE'
	 */
	unsigned char getBCE();

	/**
	 * Método accesor del atributo 'datos'
	 */
	const char *getDatos();

	/**
	 * Método modificador global
	 */
	void
	setAttr(/* Nuevo valor del caracter de sincronismo */unsigned char S,/* Nuevo valor del caracter de dirección */
														 unsigned char D,/* Nuevo valor del caracter de control */
														 unsigned char C, /* Nuevo valor del número de trama */
														 unsigned char NT,/* Nuevo valor de la longitud */
														 unsigned char L, /* Nuevo mensaje */char *datos);

	/**
	 * Devuelve la representación en cadena de la trama de datos
	 */
	std::string toString() override;
};

#endif
