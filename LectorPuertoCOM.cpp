#include "LectorPuertoCOM.h"

LectorPuertoCOM::LectorPuertoCOM() {
	mPuertoCOM = nullptr;

	esTrama = false;
	finTrama = false;
	idxTrama = 1;
	tramaAux = Trama();
}

LectorPuertoCOM::LectorPuertoCOM(ManejadorPuertoCOM *mPuertoCOM) {
	this->mPuertoCOM = mPuertoCOM;

	esTrama = false;
	finTrama = false;
	idxTrama = 1;
	tramaAux = Trama();
}

void LectorPuertoCOM::lectura() {
	char contenido = hayContenido();
	if (contenido) {
		printf("%c", contenido);
	}
}

bool LectorPuertoCOM::manPrtoCOMAbierto() {
	return mPuertoCOM != nullptr ? mPuertoCOM->getEstadoAbierto() : false;
}

char LectorPuertoCOM::hayContenido() {
	HANDLE com = mPuertoCOM->getHandle();
	// Comprueba que el manejador del puerto COM esté abierto
	return static_cast<char>(manPrtoCOMAbierto() ? RecibirCaracter(com) : 0);
}

bool LectorPuertoCOM::getEsTrama() {
	return this->esTrama;
}

bool LectorPuertoCOM::getFinTrama() {
	return this->finTrama;
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

void LectorPuertoCOM::setFinTrama(/* Nuevo valor de la bandera */bool finTrama) {
	this->finTrama = finTrama;
}

void LectorPuertoCOM::setIdxTrama(/* Nuevo valor del índice */int idxTrama) {
	this->idxTrama = idxTrama;
}
