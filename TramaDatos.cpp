#include "TramaDatos.h"

TramaDatos::TramaDatos() {
	datos = nullptr;
	L = 0;
	BCE = 0;
}

TramaDatos::TramaDatos(unsigned char S, unsigned char D, unsigned char C, unsigned char NT, unsigned char L,
					   unsigned char *datos) : Trama(S, D, C, NT) {
	this->L = L;
	this->datos = datos;
	this->BCE = 0;
}

void TramaDatos::calcularBCE() {
	// TODO - implement TramaDatos::calcularBCE
	throw "Not yet implemented";
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
