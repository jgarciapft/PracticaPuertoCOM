#include "Principal.h"
#include "ManejadorInfoUsuario.h"

ManejadorInfoUsuario::ManejadorInfoUsuario() = default;

int
ManejadorInfoUsuario::preguntarRespEntRang(const char pregunta[], const char msjError[], int limInf, int limSup) {
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

string ManejadorInfoUsuario::resumenTrama(char dir, Trama *trama) {
	string protocToString = trama->protoc_toString();
	char *cad = static_cast<char *>(malloc(sizeof(dir) + protocToString.length() + 1));

	sprintf(cad, "%c\t%s", dir, protocToString.c_str());
	const basic_string<char> &basicString = string(cad);

	return basicString;
}

string ManejadorInfoUsuario::resumenTrama(char dir, Trama *trama, unsigned char BCECalculado) {
	string protocToString = dynamic_cast<TramaDatos *>(trama)->protoc_toString(BCECalculado);
	char *cad = static_cast<char *>(malloc(sizeof(dir) + protocToString.length() + 1));

	sprintf(cad, "%c\t%s", dir, protocToString.c_str());
	const basic_string<char> &basicString = string(cad);

	return basicString;
}