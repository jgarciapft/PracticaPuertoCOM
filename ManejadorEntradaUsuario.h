#ifndef MANEJADORENTRADAUSUARIO_H
#define MANEJADORENTRADAUSUARIO_H

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
	 */
	static int preguntarRespEntRang(/* Mensaje que mostrar al usuario */
			const char pregunta[], /* L�mite inferior del rango num�rico permitido (inclusive) */
			int limInf, /* Limite superior del rango num�rico permitido (inclusive) */int limSup);
};

#endif
