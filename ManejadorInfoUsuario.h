#ifndef MANEJADORENTRADAUSUARIO_H
#define MANEJADORENTRADAUSUARIO_H

#include <iostream>
#include "CargadorManejadorPuertoCOM.h"
#include "LectorPuertoCOM.h"
#include "EscritorPuertoCOM.h"
#include "Trama.h"

/**
 * Clase de utilidad para manejar la entrada y salida de información al usuario por consola
 * 
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
 */
class ManejadorInfoUsuario {

private:
	ManejadorInfoUsuario();

public:
	/**
	 *  Resumen de la trama suministrada
	 *
	 * @param dir Dirección de la trama. Envío (E) o recepción (R)
	 * @param trama Trama a loggear
	 * @return Cadena con el resumen de la trama
	 */
	static string resumenTrama(char dir, Trama *trama);

	/**
	 * Resumen de la trama de datos suministrada
	 *
	 * @param dir Dirección de la trama. Envío (E) o recepción (R)
	 * @param trama Trama a loggear
	 * @param BCECalculado BCE calculado externamente
	 * @return Cadena con el resumen de la trama
	 */
	static string resumenTrama(char dir, Trama *trama, unsigned char BCECalculado);

	/**
	 * Obtiene una respuesta numérica del usuario a una pregunta
	 *
	 * @param pregunta Mensaje que mostrar al usuario
	 * @param msjError Mensaje de error
	 * @param limInf Límite inferior del rango numérico permitido (inclusive)
	 * @param limSup Limite superior del rango numérico permitido (inclusive)
	 */
	static int preguntarRespEntRang(const char pregunta[], const char msjError[], int limInf, int limSup);
};

#endif
