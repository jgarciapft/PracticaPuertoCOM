#include "EscritorPuertoCOM.h"

EscritorPuertoCOM::EscritorPuertoCOM() {
	mPuertoCOM = nullptr;

	finCaracter = false;
}

EscritorPuertoCOM::EscritorPuertoCOM(ManejadorPuertoCOM *mPuertoCOM) {
	this->mPuertoCOM = mPuertoCOM;

	finCaracter = false;
}

void EscritorPuertoCOM::escritura() {
	char car = static_cast<char>(getch());

	if (car == 27) setFinCaracter(true);

	if (manPrtoCOMAbierto() && !getFinCaracter()) {
		HANDLE com = mPuertoCOM->getHandle();

		printf("%c", car);
		EnviarCaracter(com, car);
	}
}

bool EscritorPuertoCOM::getFinCaracter() {
	return this->finCaracter;
}

bool EscritorPuertoCOM::manPrtoCOMAbierto() {
	return mPuertoCOM != nullptr ? mPuertoCOM->getEstadoAbierto() : false;
}

void EscritorPuertoCOM::setFinCaracter(/* Nuevo valor de la bandera */bool finCaracter) {
	this->finCaracter = finCaracter;
}
