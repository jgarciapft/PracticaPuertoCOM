#include "ManejadorPuertoCOM.h"

ManejadorPuertoCOM *ManejadorPuertoCOM::instancia = nullptr;

ManejadorPuertoCOM::ManejadorPuertoCOM() {
	estadoAbierto = false;
	handle = nullptr;
}

bool ManejadorPuertoCOM::abrirManejador(/* Constante que indica el puerto COM a elegir */
		LPCSTR nombrePuerto, /* Tasa de baudios */
		DWORD velocidad, /* Número de bits en cada byte enviado o recibido. Valor entre 4 y 8, ambos inclusive */
		BYTE numBitsXByte, /* Bit de paridad.
        0 = sin paridad
        1=impar
        2=par
        3=marca
        4=espacio */BYTE paridad, /* Bits de stop.
        0 = 1 bit
        1 = 1.5 bits
        2 = 2 bits */BYTE bitsParada) {
	if (!getEstadoAbierto()) {	// Comprueba que el puerto no esté abierto ya
		handle = AbrirPuerto(nombrePuerto, velocidad, numBitsXByte, paridad, bitsParada);
		if (getHandle() != nullptr)	// Si el se pudo abrir el manejador se actualiza la bandera de estado
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

void ManejadorPuertoCOM::setEstadoAbierto(/* Nuevo valor de la bandera de estado */boolean estadoAbierto) {
	this->estadoAbierto = estadoAbierto;
}
