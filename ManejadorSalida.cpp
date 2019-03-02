#include <cstdio>
#include "ManejadorSalida.h"

ManejadorSalida::ManejadorSalida() = default;

void ManejadorSalida::imprimirConsola(/* mensaje a imprimir por consola */const char mensaje[]) {
	std::printf("%s\n", mensaje);
}
