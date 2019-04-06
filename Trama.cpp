#include "Trama.h"
#include "Principal.h"

const std::string Trama::CONST_CONTROL_TRAMA[] = {"ENQ", "EOT", "ACK", "NACK", "STX", "DESCONOCIDO"};

Trama::Trama() {
	this->S = 0;
	this->D = 0;
	this->C = 0;
	this->NT = 0;
}

Trama::Trama(Trama *trama) {
	S = trama->getS();
	D = trama->getD();
	C = trama->getC();
	NT = trama->getNT();
}

Trama::Trama(unsigned char S, unsigned char D, unsigned char C, unsigned char NT) {
	this->S = S;
	this->D = D;
	this->C = C;
	this->NT = NT;
}

Trama* Trama::copia() {
	return new Trama(this);
}

unsigned char Trama::getS() const {
	return S;
}

unsigned char Trama::getD() const {
	return D;
}

unsigned char Trama::getC() const {
	return C;
}

unsigned char Trama::getNT() const {
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
	return "Trama " + constTipoTrama(getC());
}

std::string Trama::protoc_toString() {
	const unsigned char D = getD();
	const unsigned char NT = getNT();
	const string tipoTrama = constTipoTrama(getC());
	char *cad = static_cast<char *>(malloc(sizeof(D) + sizeof(NT) + tipoTrama.size() + 2));

	sprintf(cad, "%c\t%s\t%c", D, tipoTrama.c_str(), NT);

	const basic_string<char> &basicString = std::string(cad);
	delete cad;

	return basicString;
}

string Trama::constTipoTrama(unsigned char controlCar) {
	std::string tipoTrama;

	switch (controlCar) {
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
		case STX:
			tipoTrama = CONST_CONTROL_TRAMA[4];
			break;
		default:
			tipoTrama = CONST_CONTROL_TRAMA[5];
	}
	return tipoTrama;
}

Trama Trama::llamadaSeleccion() {
	return Trama(CONSTANTES::SINCRONISMO, 'R', ENQ, '0');
}

Trama Trama::llamadaSondeo() {
	return Trama(CONSTANTES::SINCRONISMO, 'T', ENQ, '0');
}

Trama Trama::confirmacionTramaN(unsigned char nt) {
	return Trama(CONSTANTES::SINCRONISMO, 'R', ACK, '0');
}

Trama Trama::rechazoTramaN(unsigned char nt) {
	return Trama(CONSTANTES::SINCRONISMO, 'R', NACK, '0');
}

Trama Trama::liberacion() {
	return Trama(CONSTANTES::SINCRONISMO, 'R', EOT, '0');
}
