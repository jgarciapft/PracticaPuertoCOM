#include "ManejadorEntradaUsuario.h"

ManejadorEntradaUsuario::ManejadorEntradaUsuario() = default;

int ManejadorEntradaUsuario::preguntarRespEntRang(/* Mensaje que mostrar al usuario */
		const char pregunta[], /* Mensaje de error */
		const char msjError[], /* L�mite inferior del rango num�rico permitido (inclusive) */
		int limInf, /* Limite superior del rango num�rico permitido <(inclusive) */int limSup) {

	bool selCorrecta = false; // Bandera de selecci�n correcta del usuario
	char cadAux[10]; // Cadena auxiliar en la que leer la entrada de usuario
	int entUs; // Selecci�n num�rica del usuario convertida a entero

	do {
		printf("%s\n\n", pregunta); // Muestra el mensaje de pregunta al usuario
		std::cin >> cadAux; // Lee la entrada de usuario
		entUs = strtol(cadAux, nullptr, 10); // Intenta convertir a n�mero la entrada de usuario

		if (entUs >= limInf && entUs <= limSup) // Control de opci�n
			selCorrecta = true;
		else // Opci�n inv�lida. Se muestra msj error y se vuelve a leer opci�n
			printf("%s (%s)\n", msjError, cadAux);
	} while (!selCorrecta);

	return entUs;
}
