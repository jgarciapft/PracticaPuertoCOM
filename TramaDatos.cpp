#include "TramaDatos.h"

TramaDatos::TramaDatos() {
	datos = nullptr;
	L = 0;
	BCE = 0;
}

TramaDatos::TramaDatos(unsigned char S, unsigned char D, unsigned char C, unsigned char NT, unsigned char L,
					   const char *datos) : Trama(S, D, C, NT) {
	this->L = L;
	this->datos = datos;
	this->BCE = 0;
}

void TramaDatos::calcularBCE() {
	auto BCE = static_cast<unsigned char>(datos[0]);

	// Calculo del BCE
	for (int i = 1; i < getL(); i++)
		BCE ^= datos[i];

	// Actualiza el BCE. Controla que no valga 0 ni 255
	setBCE(static_cast<unsigned char>(BCE == 0 || BCE == 255 ? 1 : BCE));
}

unsigned char TramaDatos::getL() {
	return L;
}

unsigned char TramaDatos::getBCE() {
	return BCE;
}

const char *TramaDatos::getDatos() {
	return datos;
}

void TramaDatos::setL(unsigned char L) {
	this->L = L;
}

void TramaDatos::setBCE(unsigned char BCE) {
	this->BCE = BCE;
}

void TramaDatos::setDatos(char *datos) {
	this->datos = datos;
}

void TramaDatos::setAttr(unsigned char S, unsigned char D, unsigned char C, unsigned char NT, unsigned char L,
						 char *datos) {
	this->setS(S);
	this->setD(D);
	this->setC(C);
	this->setNT(NT);
	this->setL(L);
	this->setDatos(datos);
}

std::string TramaDatos::toString() {
	return std::string(datos, getL());
}
