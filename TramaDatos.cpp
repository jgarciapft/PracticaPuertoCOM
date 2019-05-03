#include "TramaDatos.h"

const char TramaDatos::CHAR_SUSTITUCION_ERROR_BCE = 231; // Código ASCII extendido del caracter 'ç'

TramaDatos::TramaDatos() {
	datos = nullptr;
	L = 0;
	BCE = 0;
}

TramaDatos::TramaDatos(Trama *trama) : Trama(trama) {
	datos = dynamic_cast<TramaDatos *>(trama)->getDatos();
	L = dynamic_cast<TramaDatos *>(trama)->getL();
	BCE = dynamic_cast<TramaDatos *>(trama)->getBCE();
}

TramaDatos::TramaDatos(unsigned char S, unsigned char D, unsigned char C, unsigned char NT, unsigned char L,
					   const char *datos) : Trama(S, D, C, NT) {
	this->L = L;
	this->datos = datos;
	this->BCE = 0;
}

char TramaDatos::sustituirPrimerCaracter() {
	char sustituido = datos[0];

	char *datosMod = const_cast<char *>(datos);
	datosMod[0] = CHAR_SUSTITUCION_ERROR_BCE;
	setDatos(datosMod);

	return sustituido;
}

void TramaDatos::restaurarPrimerCaracter(char charSustituido) {
	char *datosMod = const_cast<char *>(datos);
	datosMod[0] = charSustituido;
	setDatos(datosMod);
}

Trama *TramaDatos::copia() {
	return new TramaDatos(this);
}

void TramaDatos::calcularBCE() {
	setBCE(calcularBCE(this));
}

unsigned char TramaDatos::calcularBCE(TramaDatos *tramaDatos) {
	auto BCE = static_cast<unsigned char>(tramaDatos->getDatos()[0]);

	// Calculo del BCE
	for (int i = 1; i < tramaDatos->getL(); i++)
		BCE ^= tramaDatos->getDatos()[i];

	// Controla que no valga 0 ni 255
	return static_cast<unsigned char>(BCE == 0 || BCE == 255 ? 1 : BCE);
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

std::string TramaDatos::protoc_toString(unsigned char BCECalculado) {
	const std::string &base = protoc_toString();
	char *cad = static_cast<char *>(malloc(base.size() + sizeof(BCECalculado) + 1));

	sprintf(cad, "%s\t%d", base.c_str(), BCECalculado);

	const std::basic_string<char> &basicString = std::string(cad);
	delete cad;

	return basicString;
}

std::string TramaDatos::protoc_toString() {
	const std::string &base = Trama::protoc_toString();
	const unsigned char BCE = getBCE();
	char *cad = static_cast<char *>(malloc(base.size() + sizeof(BCE) + 1));

	sprintf(cad, "%s\t%d", base.c_str(), BCE);

	const std::basic_string<char> &basicString = std::string(cad);
	delete cad;

	return basicString;
}
