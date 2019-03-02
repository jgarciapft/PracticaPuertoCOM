#ifndef TRAMA_H
#define TRAMA_H

#include <string>

/**
 * Clase que modela una trama genérica. Contiene:
 *
 * 	- Caracter de Sincronismo (S)
 * 	- Caracter de Dirección (D)
 * 	- Caracter de Control (C)
 * 	- Caracter de Número de Trama (NT)
 *
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
 */

class Trama {

private:
	/**
	 * Colección de códigos ASCII de tipos de trama
	 */
	enum COD_CONTROL_TRAMA {
		ENQ = 5, EOT = 4, ACK = 6, NACK = 21
	};

	/**
	 * Colección de constantes alfabéticas de tipos de control de tramas
	 */
	static const std::string CONST_CONTROL_TRAMA[];

private:
	/**
	 * Caracter de sincronismo
	 */
	unsigned char S;
	/**
	 * Caracter de dirección
	 */
	unsigned char D;
	/**
	 * Caracter de control
	 */
	unsigned char C;
	/**
	 * Caracter de número de trama
	 */
	unsigned char NT;

public:
	Trama();

	Trama(unsigned char S, unsigned char D, unsigned char C, unsigned char NT);

	/**
	 * Método accesor del atributo 'S'
	 */
	unsigned char getS();

	/**
	 * Método accesor del atributo 'D'
	 */
	unsigned char getD();

	/**
	 * Método accesor del atributo 'C'
	 */
	unsigned char getC();

	/**
	 * Método accesor del atributo 'NT'
	 */
	unsigned char getNT();

	/**
	 * Método modificador del atributo 'S'
	 */
	void setS(/* Nuevo valor del caracter de sincronismo */unsigned char S);

	/**
	 * Método modificador del atributo 'D'
	 */
	void setD(/* Nuevo valor del caracter de dirección */unsigned char D);

	/**
	 * Método modificador del atributo 'C'
	 */
	void setC(/* Nuevo valor del caracter de control */unsigned char C);

	/**
	 * Método modificador del atributo 'NT'
	 */
	void setNT(/* Nuevo valor del número de trama */unsigned char NT);

	/**
	 * Devuelve la representación en cadena de la trama
	 */
	std::string toString();
};

#endif
