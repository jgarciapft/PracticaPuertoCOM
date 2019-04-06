#ifndef TRAMA_H
#define TRAMA_H

#include <string>

/**
 * Clase que modela una trama gen�rica. Contiene:
 *
 * 	- Caracter de Sincronismo (S)
 * 	- Caracter de Direcci�n (D)
 * 	- Caracter de Control (C)
 * 	- Caracter de N�mero de Trama (NT)
 *
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */

class Trama {

protected:
	/**
	 * Colecci�n de constantes alfab�ticas de tipos de control de tramas
	 */
	static const std::string CONST_CONTROL_TRAMA[];

public:
	/**
	 * Colecci�n de c�digos ASCII de tipos de trama
	 */
	enum COD_CONTROL_TRAMA {
		STX = 2, ENQ = 5, EOT = 4, ACK = 6, NACK = 21
	};

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

	/**
	 * @return Trama de control para la operaci�n de selecci�n
	 */
	static Trama llamadaSeleccion();

	/**
	 * @return Trama de control para la operaci�n de sondeo
	 */
	static Trama llamadaSondeo();

	/**
	 * @param d Direcci�n de la trama
	 * @param nt Valor del campo de trama de la trama a confirmar
	 * @return Trama de control de confirmaci�n de trama
	 */
	static Trama confirmacionTramaN(unsigned char d, unsigned char nt);

	/**
	 * @param d Direcci�n de la trama
	 * @param nt Valor del campo de trama de la trama a rechazar
	 * @return Trama de control de rechazo de trama
	 */
	static Trama rechazoTramaN(unsigned char d, unsigned char nt);

	/**
	 * @param d Direcci�n de la trama
	 * @return Trama de control de liberaci�n
	 */
	static Trama liberacion(unsigned char d);

	Trama();

	explicit Trama(Trama *trama);

	Trama(unsigned char S, unsigned char D, unsigned char C, unsigned char NT);

	/**
	 * @return Puntero a una copia de la instacia actual
	 */
	virtual Trama *copia();

	/**
	 * M�todo accesor del atributo 'S'
	 */
	unsigned char getS() const;

	/**
	 * M�todo accesor del atributo 'D'
	 */
	unsigned char getD() const;

	/**
	 * M�todo accesor del atributo 'C'
	 */
	unsigned char getC() const;

	/**
	 * M�todo accesor del atributo 'NT'
	 */
	unsigned char getNT() const;

	/**
	 * M�todo modificador del atributo 'S'
	 *
	 * @param S Nuevo valor del caracter de sincronismo
	 */
	void setS(unsigned char S);

	/**
	 * M�todo modificador del atributo 'D'
	 *
	 * @param D Nuevo valor del caracter de direcci�n
	 */
	void setD(unsigned char D);

	/**
	 * M�todo modificador del atributo 'C'
	 *
	 * @param C Nuevo valor del caracter de control
	 */
	void setC(unsigned char C);

	/**
	 * M�todo modificador del atributo 'NT'
	 *
	 * @param NT Nuevo valor del n�mero de trama
	 */
	void setNT(unsigned char NT);

	/**
	 * M�todo modificador combinado de todos los atributos de la clase
	 *
	 * @param S Nuevo valor del caracter de sincronismo
	 * @param D Nuevo valor del caracter de direcci�n
	 * @param C Nuevo valor del caracter de control
	 * @param NT Nuevo valor del n�mero de trama
	 */
	virtual void
	setAttr(unsigned char S, unsigned char D, unsigned char C, unsigned char NT);

	/**
	 * @return Representaci�n en cadena de la trama
	 */
	virtual std::string toString();

	/**
	 * @return Representaci�n en formato especial para ser mostrado en el resumen de la comunicaci�n de protocolo
	 */
	virtual std::string protoc_toString();

	/**
	 * @param controlCar Valor del campo de control
	 * @return Cadena que reprensenta un valor del campo de contol
	 */
	std::string constTipoTrama(unsigned char controlCar);
};

#endif
