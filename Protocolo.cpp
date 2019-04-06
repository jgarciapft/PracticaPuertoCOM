
#include "Protocolo.h"

Protocolo::Protocolo(LectorPuertoCOM *lectorPuertoCom, EscritorPuertoCOM *escritorPuertoCom) {
	this->lectorPuertoCom = lectorPuertoCom;
	this->escritorPuertoCom = escritorPuertoCom;
}

LectorPuertoCOM *Protocolo::getLectorPuertoCOM() {
	return lectorPuertoCom;
}

EscritorPuertoCOM *Protocolo::getEscritorPuertoCOM() {
	return escritorPuertoCom;
}

Protocolo::~Protocolo() {}
