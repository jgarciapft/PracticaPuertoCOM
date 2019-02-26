#include "LectorPuertoCOM.h"

void LectorPuertoCOM::setEsTrama(/* Nuevo valor de la bandera */bool esTrama) {
	this->esTrama = esTrama;
}

void LectorPuertoCOM::setFinTrama(/* Nuevo valor de la bandera */bool finTrama) {
	this->finTrama = finTrama;
}

void LectorPuertoCOM::setIdxTrama(/* Nuevo valor del índice */int idxTrama) {
	this->idxTrama = idxTrama;
}

LectorPuertoCOM::LectorPuertoCOM() {
	// TODO - implement LectorPuertoCOM::LectorPuertoCOM
	throw "Not yet implemented";
}

LectorPuertoCOM::LectorPuertoCOM(ManejadorPuertoCOM mPuertoCOM) {
	// TODO - implement LectorPuertoCOM::LectorPuertoCOM
	throw "Not yet implemented";
}

char LectorPuertoCOM::lectura() {
	// TODO - implement LectorPuertoCOM::lectura
	throw "Not yet implemented";
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
