#include "CargadorManejadorPuertoCOM.h"

CargadorManejadorPuertoCOM::CargadorManejadorPuertoCOM() {
	// TODO - implement CargadorManejadorPuertoCOM::CargadorManejadorPuertoCOM
	throw "Not yet implemented";
}

CargadorManejadorPuertoCOM::CargadorManejadorPuertoCOM(DWORD velocidad, BYTE numBitsXByte, BYTE paridad,
													   BYTE bitsParada) {
	// TODO - implement CargadorManejadorPuertoCOM::CargadorManejadorPuertoCOM
	throw "Not yet implemented";
}

bool CargadorManejadorPuertoCOM::inicializarManejador() {
	// TODO - implement CargadorManejadorPuertoCOM::inicializarManejador
	throw "Not yet implemented";
}

DWORD CargadorManejadorPuertoCOM::getVelocidad() {
	return this->velocidad;
}

BYTE CargadorManejadorPuertoCOM::getNumBitsXByte() {
	return this->numBitsXByte;
}

BYTE CargadorManejadorPuertoCOM::getParidad() {
	return this->paridad;
}

BYTE CargadorManejadorPuertoCOM::getBitsParada() {
	return this->bitsParada;
}

void CargadorManejadorPuertoCOM::setVelocidad(/* Nueva tasa de baudios */DWORD velocidad) {
	this->velocidad = velocidad;
}

void
CargadorManejadorPuertoCOM::setNumBitsXByte(/* Nuevo número de bits por byte enviado o recibido */BYTE numBitsXByte) {
	this->numBitsXByte = numBitsXByte;
}

void CargadorManejadorPuertoCOM::setParidad(/* Nuevo modo de paridad */BYTE paridad) {
	this->paridad = paridad;
}

void CargadorManejadorPuertoCOM::setBitsParada(/* Nuevo número de bits de parada */BYTE bitsParada) {
	this->bitsParada = bitsParada;
}
