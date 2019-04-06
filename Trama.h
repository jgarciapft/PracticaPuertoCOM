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

protected:
	/**
	 * Colección de constantes alfabéticas de tipos de control de tramas
	 */
	static const std::string CONST_CONTROL_TRAMA[];

public:
	/**
	 * Colección de códigos ASCII de tipos de trama
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

	/**
	 * @return Trama de control para la operación de selección
	 */
	static Trama llamadaSeleccion();

	/**
	 * @return Trama de control para la operación de sondeo
	 */
	static Trama llamadaSondeo();

	/**
	 * @param d Dirección de la trama
	 * @param nt Valor del campo de trama de la trama a confirmar
	 * @return Trama de control de confirmación de trama
	 */
	static Trama confirmacionTramaN(unsigned char d, unsigned char nt);

	/**
	 * @param d Dirección de la trama
	 * @param nt Valor del campo de trama de la trama a rechazar
	 * @return Trama de control de rechazo de trama
	 */
	static Trama rechazoTramaN(unsigned char d, unsigned char nt);

	/**
	 * @param d Dirección de la trama
	 * @return Trama de control de liberación
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
	 * Método accesor del atributo 'S'
	 */
	unsigned char getS() const;

	/**
	 * Método accesor del atributo 'D'
	 */
	unsigned char getD() const;

	/**
	 * Método accesor del atributo 'C'
	 */
	unsigned char getC() const;

	/**
	 * Método accesor del atributo 'NT'
	 */
	unsigned char getNT() const;

	/**
	 * Método modificador del atributo 'S'
	 *
	 * @param S Nuevo valor del caracter de sincronismo
	 */
	void setS(unsigned char S);

	/**
	 * Método modificador del atributo 'D'
	 *
	 * @param D Nuevo valor del caracter de dirección
	 */
	void setD(unsigned char D);

	/**
	 * Método modificador del atributo 'C'
	 *
	 * @param C Nuevo valor del caracter de control
	 */
	void setC(unsigned char C);

	/**
	 * Método modificador del atributo 'NT'
	 *
	 * @param NT Nuevo valor del número de trama
	 */
	void setNT(unsigned char NT);

	/**
	 * Método modificador combinado de todos los atributos de la clase
	 *
	 * @param S Nuevo valor del caracter de sincronismo
	 * @param D Nuevo valor del caracter de dirección
	 * @param C Nuevo valor del caracter de control
	 * @param NT Nuevo valor del número de trama
	 */
	virtual void
	setAttr(unsigned char S, unsigned char D, unsigned char C, unsigned char NT);

	/**
	 * @return Representación en cadena de la trama
	 */
	virtual std::string toString();

	/**
	 * @return Representación en formato especial para ser mostrado en el resumen de la comunicación de protocolo
	 */
	virtual std::string protoc_toString();

	/**
	 * @param controlCar Valor del campo de control
	 * @return Cadena que reprensenta un valor del campo de contol
	 */
	std::string constTipoTrama(unsigned char controlCar);
};

#endif
