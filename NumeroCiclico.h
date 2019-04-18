
#ifndef PRACTICAPUERTOCOM_NUMEROCICLICO_H
#define PRACTICAPUERTOCOM_NUMEROCICLICO_H

/**
 * Clase que implementa un generador de n�meros c�clicos (en incrementos de 1) entre dos valores,
 * un l�mite inferior y un l�mite superior, ambos inclusive. Siempre comienza por el valor del l�mite inferior
 *
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
class NumeroCiclico {

private:
	/**
	 * L�mite inferior de la serie num�rica
	 */
	int limiteInf;
	/**
	 * L�mite superior de la serie num�rica
	 */
	int limiteSup;
	/**
	 * Valor que determinar� el siguiente a generar
	 */
	int numeroActual;

public:
	/**
	 * @param limiteInf L�mite inferior de la serie num�rica
	 * @param limiteSup L�mite superior de la serie num�rica
	 */
	NumeroCiclico(int limiteInf, int limiteSup);

	/**
	 * @return Siguiente n�mero en la serie
	 */
	int siguiente();

	/**
	 * Reinicia el estado interno del generador
	 */
	void reset();
};


#endif //PRACTICAPUERTOCOM_NUMEROCICLICO_H
