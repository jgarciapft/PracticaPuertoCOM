
#ifndef PRACTICAPUERTOCOM_NUMEROCICLICO_H
#define PRACTICAPUERTOCOM_NUMEROCICLICO_H

/**
 * Clase que implementa un generador de números cíclicos entre dos valores, un límite inferior y un límite superior,
 * ambos inclusive. Siempre comienza por el valor del límite inferior
 *
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
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
