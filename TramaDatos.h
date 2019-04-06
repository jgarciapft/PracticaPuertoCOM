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
	const char *datos;
	/**
	 * Bloque de control de errores
	 */
	unsigned char BCE;

	/**
	 * Método modificador del atributo 'BCE'
	 *
	 * @param BCE Nuevo BCE
	 */
	void setBCE(unsigned char BCE);

public:

	/**
	 * TODO Añadir modo de protocolo
	 *
	 * @param nt Número de trama
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
	 * Método modificador del atributo 'L'
 	 *
 	 * @param L Nuevo valor de la longitud
	 */
	void setL(unsigned char L);

	/**
	 * Método modificador del atributo 'datos'
	 *
	 * @param datos Nuevo mensaje
	 */
	void setDatos(char *datos);

	/**
	 * Método modificador global
	 *
	 * @param S Nuevo valor del caracter de sincronismo
	 * @param D Nuevo valor del caracter de dirección
	 * @param C Nuevo valor del caracter de control
	 * @param NT Nuevo valor del número de trama
	 * @param L Nuevo valor de la longitud
	 * @param datos Nuevo mensaje
	 */
	void
	setAttr(unsigned char S, unsigned char D, unsigned char C, unsigned char NT, unsigned char L, char *datos);

	/**
	 * Devuelve la representación en cadena de la trama de datos
	 */
	std::string toString() override;
};

#endif
