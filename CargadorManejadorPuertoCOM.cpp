#include "CargadorManejadorPuertoCOM.h"

CargadorManejadorPuertoCOM::CargadorManejadorPuertoCOM() {
	nombrePuerto = "UNKNOWN";
	velocidad = 0;
	numBitsXByte = 0;
	paridad = 0;
	bitsParada = 0;
}

CargadorManejadorPuertoCOM::CargadorManejadorPuertoCOM(LPCSTR nombrePuerto, DWORD velocidad, BYTE numBitsXByte,
													   BYTE paridad,
													   BYTE bitsParada) {
	this->nombrePuerto = nombrePuerto;
	this->velocidad = velocidad;
	this->numBitsXByte = numBitsXByte;
	this->paridad = paridad;
	this->bitsParada = bitsParada;
}

bool CargadorManejadorPuertoCOM::inicializarManejador() {
	return ManejadorPuertoCOM::recuperarInstancia()->abrirManejador(getNombrePuerto(), getVelocidad(),
																	getNumBitsXByte(), getParidad(),
																	getBitsParada());
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
CargadorManejadorPuertoCOM::setNumBitsXByte(/* Nuevo n�mero de bits por byte enviado o recibido */BYTE numBitsXByte) {
	this->numBitsXByte = numBitsXByte;
}

void CargadorManejadorPuertoCOM::setParidad(/* Nuevo modo de paridad */BYTE paridad) {
	this->paridad = paridad;
}

void CargadorManejadorPuertoCOM::setBitsParada(/* Nuevo n�mero de bits de parada */BYTE bitsParada) {
	this->bitsParada = bitsParada;
}

LPCSTR CargadorManejadorPuertoCOM::getNombrePuerto() {
	return this->nombrePuerto;
}

void CargadorManejadorPuertoCOM::setNombrePuerto(LPCSTR nombrePuerto) {
	this->nombrePuerto = nombrePuerto;
}
