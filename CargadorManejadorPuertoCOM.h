#ifndef CARGADORMANEJADORPUERTOCOM_H
#define CARGADORMANEJADORPUERTOCOM_H

#include "ManejadorPuertoCOM.h"
#include "ManejadorEntradaUsuario.h"

/**
 * Clase encargada de definir los parámetros de inicialización del manejador del puerto COM y de realizar la acción de inicializar el mismo
 * 
 * 
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
 */
class CargadorManejadorPuertoCOM {

private:
	/**
	 * Mensaje de éxito al abrir el puerto COM
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
	 * Número de bits en cada byte enviado o recibido. Valor entre 4 y 8, ambos inclusive
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
	 * Método accesor del atributo 'velocidad'
	 */
	DWORD getVelocidad();

	/**
	 * Método accesor del atributo 'numBitsXByte'
	 */
	BYTE getNumBitsXByte();

	/**
	 * Método accesor del atributo 'paridad'
	 */
	BYTE getParidad();

	/**
	 * Método accesor del atributo 'bitsParada'
	 */
	BYTE getBitsParada();

	/**
	 * Método modificador del atributo 'velocidad'
	 */
	void setVelocidad(/* Nueva tasa de baudios */DWORD velocidad);

	/**
	 * Método modificador del atributo 'numBitsXByte'
	 */
	void setNumBitsXByte(/* Nuevo número de bits por byte enviado o recibido */BYTE numBitsXByte);

	/**
	 * Método modificador del atributo 'paridad'
	 */
	void setParidad(/* Nuevo modo de paridad */BYTE paridad);

	/**
	 * Método modificador del atributo 'bitsParada'
	 */
	void setBitsParada(/* Nuevo número de bits de parada */BYTE bitsParada);

	/**
	 * Método accesor del atributo 'nombrePuerto'
	 */
	LPCSTR getNombrePuerto();

	/**
	 * Método modificador del atributo 'nombrePuerto'
	 */
	void setNombrePuerto(LPCSTR nombrePuerto);
};

#endif
