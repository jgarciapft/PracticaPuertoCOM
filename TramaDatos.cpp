#include "TramaDatos.h"

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

Trama *TramaDatos::copia() {
	return new TramaDatos(this);
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

TramaDatos TramaDatos::envioDatosN(unsigned char d, unsigned char nt, unsigned char lon, const char *datos) {
	TramaDatos tramaDatos = TramaDatos(CONSTANTES::SINCRONISMO, d, CONSTANTES::STX, nt, lon, datos);
	tramaDatos.calcularBCE();

	return tramaDatos;
}
