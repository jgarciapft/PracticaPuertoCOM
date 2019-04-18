#ifndef MANEJADORENTRADAUSUARIO_H
#define MANEJADORENTRADAUSUARIO_H

#include <iostream>
#include "CargadorManejadorPuertoCOM.h"
#include "LectorPuertoCOM.h"
#include "EscritorPuertoCOM.h"
#include "Trama.h"

/**
 * Clase de utilidad para manejar la entrada y salida de informaci�n al usuario por consola
 * 
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
class ManejadorInfoUsuario {

private:
	ManejadorInfoUsuario();

public:
	/**
	 *  Resumen de la trama suministrada
	 *
	 * @param dir Direcci�n de la trama. Env�o (E) o recepci�n (R)
	 * @param trama Trama a loggear
	 * @return Cadena con el resumen de la trama
	 */
	static string resumenTrama(char dir, Trama *trama);

	/**
	 * Resumen de la trama de datos suministrada
	 *
	 * @param dir Direcci�n de la trama. Env�o (E) o recepci�n (R)
	 * @param trama Trama a loggear
	 * @param BCECalculado BCE calculado externamente
	 * @return Cadena con el resumen de la trama
	 */
	static string resumenTrama(char dir, Trama *trama, unsigned char BCECalculado);

	/**
	 * Obtiene una respuesta num�rica del usuario a una pregunta
	 *
	 * @param pregunta Mensaje que mostrar al usuario
	 * @param msjError Mensaje de error
	 * @param limInf L�mite inferior del rango num�rico permitido (inclusive)
	 * @param limSup Limite superior del rango num�rico permitido (inclusive)
	 */
	static int preguntarRespEntRang(const char pregunta[], const char msjError[], int limInf, int limSup);
};

#endif
