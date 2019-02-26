#ifndef TRAMA_H
#define TRAMA_H

#include <string>

/**
 * Clase que modela una trama gen�rica
 * 
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
class Trama {

private:
	/**
	 * Caracter de sincronismo
	 */
	unsigned char S;
	/**
	 * Caracter de direcci�n
	 */
	unsigned char D;
	/**
	 * Caracter de control
	 */
	unsigned char C;
	/**
	 * Caracter de n�mero de trama
	 */
	unsigned char NT;

public:
	Trama();

	Trama(unsigned char S, unsigned char D, unsigned char C, unsigned char N);

	/**
	 * M�todo accesor del atributo 'S'
	 */
	unsigned char getS();

	/**
	 * M�todo accesor del atributo 'D'
	 */
	unsigned char getD();

	/**
	 * M�todo accesor del atributo 'C'
	 */
	unsigned char getC();

	/**
	 * M�todo accesor del atributo 'NT'
	 */
	unsigned char getNT();

	/**
	 * M�todo modificador del atributo 'S'
	 */
	void setS(/* Nuevo valor del caracter de sincronismo */unsigned char S);

	/**
	 * M�todo modificador del atributo 'D'
	 */
	void setD(/* Nuevo valor del caracter de direcci�n */unsigned char D);

	/**
	 * M�todo modificador del atributo 'C'
	 */
	void setC(/* Nuevo valor del caracter de control */unsigned char C);

	/**
	 * M�todo modificador del atributo 'NT'
	 */
	void setNT(/* Nuevo valor del n�mero de trama */unsigned char NT);

	/**
	 * Devuelve la representaci�n en cadena de la trama
	 */
	std::string toString();
};

#endif
