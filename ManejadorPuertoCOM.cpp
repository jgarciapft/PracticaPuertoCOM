#include "ManejadorPuertoCOM.h"

ManejadorPuertoCOM *ManejadorPuertoCOM::instancia = nullptr;

ManejadorPuertoCOM::ManejadorPuertoCOM() {
	estadoAbierto = false;
	handle = nullptr;
}

bool ManejadorPuertoCOM::abrirManejador(LPCSTR nombrePuerto, DWORD velocidad, BYTE numBitsXByte, BYTE paridad,
										BYTE bitsParada) {
	if (!getEstadoAbierto()) { // Comprueba que el puerto no esté abierto ya
		handle = AbrirPuerto(nombrePuerto, velocidad, numBitsXByte, paridad, bitsParada);
		if (getHandle() != nullptr) // Si el se pudo abrir el manejador se actualiza la bandera de estado
			setEstadoAbierto(true);
	}

	return getEstadoAbierto();
}

void ManejadorPuertoCOM::cerrarManejador() {
	CerrarPuerto(handle);
	setEstadoAbierto(false);
}

ManejadorPuertoCOM *ManejadorPuertoCOM::recuperarInstancia() {
	if (instancia == nullptr)
		instancia = new ManejadorPuertoCOM();
	return instancia;
}

HANDLE ManejadorPuertoCOM::getHandle() {
	return handle;
}

bool ManejadorPuertoCOM::getEstadoAbierto() {
	return estadoAbierto;
}

void ManejadorPuertoCOM::setEstadoAbierto(boolean estadoAbierto) {
	this->estadoAbierto = estadoAbierto;
}
