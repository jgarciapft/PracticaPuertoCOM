#include "LectorPuertoCOM.h"

LectorPuertoCOM::LectorPuertoCOM() {
	mPuertoCOM = nullptr;

	esTrama = false;
	idxTrama = 1;
	tramaAux = Trama();
}

LectorPuertoCOM::LectorPuertoCOM(ManejadorPuertoCOM *mPuertoCOM) {
	this->mPuertoCOM = mPuertoCOM;

	esTrama = false;
	idxTrama = 1;
	tramaAux = Trama();
}

void LectorPuertoCOM::lectura() {
	char car = hayContenido(); // Comprueba si hay car. Si lo hay lo lee

	if (car) {
		if (!getEsTrama()) { // Comprueba si est� en proceso de leer una trama
			if (car == CONSTANTES::SINCRONISMO) { // Detecta caracter de sincronismo. Es trama
				setEsTrama(true);
				leerTrama(car);
			} else {
				printf("%c", car); // No es trama. Es un caracter
			}
		} else { // Est� en proceso de leer una trama
			leerTrama(car);
		}
	}
}

bool LectorPuertoCOM::manPrtoCOMAbierto() {
	return mPuertoCOM != nullptr ? mPuertoCOM->getEstadoAbierto() : false;
}

char LectorPuertoCOM::hayContenido() {
	HANDLE com = mPuertoCOM->getHandle();
	// Comprueba que el manejador del puerto COM est� abierto
	return static_cast<char>(manPrtoCOMAbierto() ? RecibirCaracter(com) : 0);
}

bool LectorPuertoCOM::getEsTrama() {
	return this->esTrama;
}

int LectorPuertoCOM::getIdxTrama() {
	return this->idxTrama;
}

Trama LectorPuertoCOM::getTramaAux() {
	return this->tramaAux;
}

void LectorPuertoCOM::setEsTrama(/* Nuevo valor de la bandera */bool esTrama) {
	this->esTrama = esTrama;
}

void LectorPuertoCOM::setIdxTrama(/* Nuevo valor del �ndice */int idxTrama) {
	this->idxTrama = idxTrama;
}

void LectorPuertoCOM::leerTrama(char car) {
	switch (getIdxTrama()) { // Determina en qu� campo de la trama hay que escribir
		case 1: // Campo de Sincronismo
			getTramaAux().setS(car);
			setIdxTrama(getIdxTrama() + 1);
			break;
		case 2: // Campo de Direcci�n
			getTramaAux().setD(car);
			setIdxTrama(getIdxTrama() + 1);
			break;
		case 3: // Campo de Control
			getTramaAux().setC(car);
			setIdxTrama(getIdxTrama() + 1);
			break;
		case 4: // Campo de N�mero de Trama
			getTramaAux().setNT(car);

			// Imprime la trama recibida
			printf("%s [%s]", "Recibido", getTramaAux().toString().c_str());

			// Reinicia las banderas de trama
			setIdxTrama(1);
			setEsTrama(false);
	}
}
