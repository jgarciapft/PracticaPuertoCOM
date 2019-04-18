
#include "NumeroCiclico.h"

NumeroCiclico::NumeroCiclico(int limiteInf, int limiteSup) : limiteInf(limiteInf), limiteSup(limiteSup) {
	numeroActual = limiteInf;
}

unsigned char NumeroCiclico::siguiente() {
	int sigNumero = numeroActual;

	if (numeroActual < limiteSup) numeroActual++;
	else reset();

	// Conversi�n de n�mero a ASCII
	return sigNumero + 48;
}

void NumeroCiclico::reset() {
	numeroActual = limiteInf;
}
