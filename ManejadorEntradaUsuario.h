#ifndef MANEJADORENTRADAUSUARIO_H
#define MANEJADORENTRADAUSUARIO_H

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
	 */
	static int preguntarRespEntRang(/* Mensaje que mostrar al usuario */
			const char pregunta[], /* Límite inferior del rango numérico permitido (inclusive) */
			int limInf, /* Limite superior del rango numérico permitido (inclusive) */int limSup);
};

#endif
