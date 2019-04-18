
#ifndef PRACTICAPUERTOCOM_NUMEROCICLICO_H
#define PRACTICAPUERTOCOM_NUMEROCICLICO_H

/**
 * Clase que implementa un generador de números cíclicos (en incrementos de 1) entre dos valores,
 * un límite inferior y un límite superior, ambos inclusive. Siempre comienza por el valor del límite inferior
 *
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
 */
class NumeroCiclico {

private:
	/**
	 * Límite inferior de la serie numérica
	 */
	int limiteInf;
	/**
	 * Límite superior de la serie numérica
	 */
	int limiteSup;
	/**
	 * Valor que determinará el siguiente a generar
	 */
	int numeroActual;

public:
	/**
	 * @param limiteInf Límite inferior de la serie numérica
	 * @param limiteSup Límite superior de la serie numérica
	 */
	NumeroCiclico(int limiteInf, int limiteSup);

	/**
	 * @return Siguiente número en la serie
	 */
	int siguiente();

	/**
	 * Reinicia el estado interno del generador
	 */
	void reset();
};


#endif //PRACTICAPUERTOCOM_NUMEROCICLICO_H
