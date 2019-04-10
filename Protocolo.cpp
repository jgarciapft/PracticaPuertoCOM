
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

string Protocolo::repTrama(char dir, Trama *trama) {
	string protocToString = trama->protoc_toString();
	char *cad = static_cast<char *>(malloc(sizeof(dir) + protocToString.length() + 1));

	sprintf(cad, "%c\t%s", dir, protocToString.c_str());
	const std::basic_string<char> &basicString = std::string(cad);
	delete cad;

	return basicString;
}

string Protocolo::repTrama(char dir, Trama *trama, unsigned char BCECalculado) {
	string protocToString = dynamic_cast<TramaDatos *>(trama)->protoc_toString(BCECalculado);
	char *cad = static_cast<char *>(malloc(sizeof(dir) + protocToString.length() + 1));

	sprintf(cad, "%c\t%s", dir, protocToString.c_str());
	const std::basic_string<char> &basicString = std::string(cad);
	delete cad;

	return basicString;
}
