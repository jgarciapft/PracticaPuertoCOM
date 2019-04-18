
#include "NumeroCiclico.h"

NumeroCiclico::NumeroCiclico(int limiteInf, int limiteSup) : limiteInf(limiteInf), limiteSup(limiteSup) {
	numeroActual = limiteInf;
}

int NumeroCiclico::siguiente() {
	int sigNumero = numeroActual;

	if (numeroActual < limiteSup) numeroActual++;
	else reset();

	return sigNumero;
}

void NumeroCiclico::reset() {
	numeroActual = limiteInf;
}
