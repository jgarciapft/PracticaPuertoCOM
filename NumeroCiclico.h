
#ifndef PRACTICAPUERTOCOM_NUMEROCICLICO_H
#define PRACTICAPUERTOCOM_NUMEROCICLICO_H

/**
 * Clase que implementa un generador de n�meros c�clicos entre dos valores, un l�mite inferior y un l�mite superior,
 * ambos inclusive. Siempre comienza por el valor del l�mite inferior
 *
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
class NumeroCiclico {

private:
	int limiteInf;
	int limiteSup;
	int numeroActual;

public:
	NumeroCiclico(int limiteInf, int limiteSup);

	int siguiente();

	void reset();
};


#endif //PRACTICAPUERTOCOM_NUMEROCICLICO_H
