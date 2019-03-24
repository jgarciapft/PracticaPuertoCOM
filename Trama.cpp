#include "Trama.h"

const std::string Trama::CONST_CONTROL_TRAMA[] = {"ENQ", "EOT", "ACK", "NACK", "DESCONOCIDO"};

Trama::Trama() = default;

Trama::Trama(unsigned char S, unsigned char D, unsigned char C, unsigned char NT) {
	this->S = S;
	this->D = D;
	this->C = C;
	this->NT = NT;
}

unsigned char Trama::getS() {
	return S;
}

unsigned char Trama::getD() {
	return D;
}

unsigned char Trama::getC() {
	return C;
}

unsigned char Trama::getNT() {
	return NT;
}

void Trama::setS(unsigned char S) {
	this->S = S;
}

void Trama::setD(unsigned char D) {
	this->D = D;
}

void Trama::setC(unsigned char C) {
	this->C = C;
}

void Trama::setNT(unsigned char NT) {
	this->NT = NT;
}

void Trama::setAttr(unsigned char S, unsigned char D, unsigned char C, unsigned char NT) {
	setS(S);
	setD(D);
	setC(C);
	setNT(NT);
}

std::string Trama::toString() {
	std::string tipoTrama;

	switch (getC()) {
		case ENQ:
			tipoTrama = CONST_CONTROL_TRAMA[0];
			break;
		case EOT:
			tipoTrama = CONST_CONTROL_TRAMA[1];
			break;
		case ACK:
			tipoTrama = CONST_CONTROL_TRAMA[2];
			break;
		case NACK:
			tipoTrama = CONST_CONTROL_TRAMA[3];
			break;
		default:
			tipoTrama = CONST_CONTROL_TRAMA[4];
	}

	return "Trama " + tipoTrama;
}
