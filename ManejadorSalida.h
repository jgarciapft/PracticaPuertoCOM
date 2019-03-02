#ifndef MANEJADORSALIDA_H
#define MANEJADORSALIDA_H

/**
 * Clase de utilidad para manejar la salida del programa por consola
 * 
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
 */
class ManejadorSalida {


public:
	ManejadorSalida();

	/**
	 * Imprime por consola en una línea un determinado mensaje
	 */
	static void imprimirConsola(/* mensaje a imprimir por consola */const char mensaje[]);
};

#endif
