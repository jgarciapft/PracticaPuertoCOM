#include "TramaDatos.h"

TramaDatos::TramaDatos() {
	// TODO - implement TramaDatos::TramaDatos
	throw "Not yet implemented";
}

void TramaDatos::Trama(unsigned char S, unsigned char D, unsigned char C, unsigned char NT, unsigned char L,
					   unsigned char *datos) {
	this->setS(S);
	this->setD(D);
	this->setC(C);
	this->setNT(NT);
	// Parte específica de las tramas de datos
	this->L = L;
	this->datos = datos;
	this->BCE = datos[0];
}

unsigned char TramaDatos::getL() {
	return L;
}

unsigned char TramaDatos::getBCE() {
	return BCE;
}

void TramaDatos::setL(/* Nuevo valor de la longitud */unsigned char L) {
	this->L = L;
}

void TramaDatos::setBCE(/* Nuevo valor del BCE */unsigned char BCE) {
	this->BCE = BCE;
}

void TramaDatos::calcularBCE() {
	// TODO - implement TramaDatos::calcularBCE
	throw "Not yet implemented";
}

void TramaDatos::setAttr(unsigned char S, unsigned char D, unsigned char C, unsigned char NT, unsigned char L,
						 unsigned char *datos) {
	this->setS(S);
	this->setD(D);
	this->setC(C);
	this->setNT(NT);
	this->setL(L);
	this->datos = datos;
}

std::string TramaDatos::toString() {
	// TODO - implement TramaDatos::toString
	throw "Not yet implemented";
}
