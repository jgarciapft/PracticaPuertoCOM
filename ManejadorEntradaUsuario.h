#ifndef MANEJADORENTRADAUSUARIO_H
#define MANEJADORENTRADAUSUARIO_H

#include <iostream>

/**
 * Clase de utilidad para manejar la entrada de usuario por consola
 * 
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
class ManejadorEntradaUsuario {


public:
	ManejadorEntradaUsuario();

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
