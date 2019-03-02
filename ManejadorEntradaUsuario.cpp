#include "ManejadorEntradaUsuario.h"

ManejadorEntradaUsuario::ManejadorEntradaUsuario() = default;

int ManejadorEntradaUsuario::preguntarRespEntRang(/* Mensaje que mostrar al usuario */
		const char pregunta[], /* Mensaje de error */
		const char msjError[], /* Límite inferior del rango numérico permitido (inclusive) */
		int limInf, /* Limite superior del rango numérico permitido <(inclusive) */int limSup) {

	bool selCorrecta = false; // Bandera de selección correcta del usuario
	char cadAux[10]; // Cadena auxiliar en la que leer la entrada de usuario
	int entUs; // Selección numérica del usuario convertida a entero

	do {
		printf("%s\n\n", pregunta); // Muestra el mensaje de pregunta al usuario
		std::cin >> cadAux; // Lee la entrada de usuario
		entUs = strtol(cadAux, nullptr, 10); // Intenta convertir a número la entrada de usuario

		if (entUs >= limInf && entUs <= limSup) // Control de opción
			selCorrecta = true;
		else // Opción inválida. Se muestra msj error y se vuelve a leer opción
			printf("%s (%s)\n", msjError, cadAux);
	} while (!selCorrecta);

	return entUs;
}
