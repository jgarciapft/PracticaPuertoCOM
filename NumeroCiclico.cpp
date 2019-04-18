
#include "NumeroCiclico.h"

NumeroCiclico::NumeroCiclico(int limiteInf, int limiteSup) : limiteInf(limiteInf), limiteSup(limiteSup) {
	numeroActual = limiteInf;
}

int NumeroCiclico::siguiente() {
	if (numeroActual <= limiteSup) numeroActual++;
	else numeroActual = limiteInf;

	return numeroActual;
}

void NumeroCiclico::reset() {
	numeroActual = limiteInf;
}
