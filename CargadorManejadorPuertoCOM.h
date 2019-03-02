#ifndef CARGADORMANEJADORPUERTOCOM_H
#define CARGADORMANEJADORPUERTOCOM_H

#include "ManejadorPuertoCOM.h"
#include "ManejadorEntradaUsuario.h"

/**
 * Clase encargada de definir los par�metros de inicializaci�n del manejador del puerto COM y de realizar la acci�n de inicializar el mismo
 * 
 * 
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
class CargadorManejadorPuertoCOM {

private:
	/**
	 * Mensaje de �xito al abrir el puerto COM
	 */
	static const char MSJ_PUERTO_ABIERTO[];
	/**
	 * Mensaje de error al abrir el puerto COM
	 */
	static const char MSJ_ERROR_ABRIR_PUERTO[];

private:
	/**
	 * Constante asociada al puerto COM
	 */
	LPCSTR nombrePuerto;
	/**
	 * Tasa de baudios
	 */
	DWORD velocidad;
	/**
	 * N�mero de bits en cada byte enviado o recibido. Valor entre 4 y 8, ambos inclusive
	 */
	BYTE numBitsXByte;
	/**
	 * Bit de paridad.
	 *         0 = sin paridad
	 *         1=impar
	 *         2=par
	 *         3=marca
	 *         4=espacio
	 */
	BYTE paridad;
	/**
	 * Bits de stop.
	 *         0 = 1 bit
	 *         1 = 1.5 bits
	 *         2 = 2 bits
	 */
	BYTE bitsParada;

public:
	CargadorManejadorPuertoCOM();

	CargadorManejadorPuertoCOM(LPCSTR nombrePuerto, DWORD velocidad, BYTE numBitsXByte, BYTE paridad, BYTE bitsParada);

	/**
	 * Intenta inicializar el manejador del puerto COM con los valores indicados. Devuelve 'TRUE' si el manejador fue correctamente inicializado, 'FALSO' en otro caso
	 */
	bool inicializarManejador();

	/**
	 * M�todo accesor del atributo 'velocidad'
	 */
	DWORD getVelocidad();

	/**
	 * M�todo accesor del atributo 'numBitsXByte'
	 */
	BYTE getNumBitsXByte();

	/**
	 * M�todo accesor del atributo 'paridad'
	 */
	BYTE getParidad();

	/**
	 * M�todo accesor del atributo 'bitsParada'
	 */
	BYTE getBitsParada();

	/**
	 * M�todo modificador del atributo 'velocidad'
	 */
	void setVelocidad(/* Nueva tasa de baudios */DWORD velocidad);

	/**
	 * M�todo modificador del atributo 'numBitsXByte'
	 */
	void setNumBitsXByte(/* Nuevo n�mero de bits por byte enviado o recibido */BYTE numBitsXByte);

	/**
	 * M�todo modificador del atributo 'paridad'
	 */
	void setParidad(/* Nuevo modo de paridad */BYTE paridad);

	/**
	 * M�todo modificador del atributo 'bitsParada'
	 */
	void setBitsParada(/* Nuevo n�mero de bits de parada */BYTE bitsParada);

	/**
	 * M�todo accesor del atributo 'nombrePuerto'
	 */
	LPCSTR getNombrePuerto();

	/**
	 * M�todo modificador del atributo 'nombrePuerto'
	 */
	void setNombrePuerto(LPCSTR nombrePuerto);
};

#endif
