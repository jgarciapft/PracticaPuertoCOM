#ifndef MANEJADORENTRADAUSUARIO_H
#define MANEJADORENTRADAUSUARIO_H

#include <iostream>

/**
 * Clase de utilidad para manejar la entrada de usuario por consola
 * 
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
 */
class ManejadorEntradaUsuario {


public:
	ManejadorEntradaUsuario();

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
