
#include "NumeroCiclico.h"

NumeroCiclico::NumeroCiclico(int limiteInf, int limiteSup) : limiteInf(limiteInf), limiteSup(limiteSup) {
	numeroActual = limiteInf;
}

unsigned char NumeroCiclico::siguiente() {
	int sigNumero = numeroActual;

	if (numeroActual < limiteSup) numeroActual++;
	else reset();

	// Conversión de número a ASCII
	return sigNumero + 48;
}

void NumeroCiclico::reset() {
	numeroActual = limiteInf;
}
