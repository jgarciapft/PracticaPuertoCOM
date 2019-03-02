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

	switch (car) {
		case CONSTANTES::ESCAPE:
			setFinCaracter(true);
			break;
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
