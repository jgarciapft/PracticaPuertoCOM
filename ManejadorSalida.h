#ifndef MANEJADORSALIDA_H
#define MANEJADORSALIDA_H

/**
 * Clase de utilidad para manejar la salida del programa por consola
 * 
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
class ManejadorSalida {


public:
	ManejadorSalida();

	/**
	 * Imprime por consola en una l�nea un determinado mensaje
	 */
	static void imprimirConsola(/* mensaje a imprimir por consola */const char mensaje[]);
};

#endif
