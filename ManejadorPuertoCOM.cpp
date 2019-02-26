#include "ManejadorPuertoCOM.h"

ManejadorPuertoCOM::ManejadorPuertoCOM() {
	// TODO - implement ManejadorPuertoCOM::ManejadorPuertoCOM()
	throw "Not yet implemented";
}

void ManejadorPuertoCOM::setEstadoAbierto(/* Nuevo valor de la bandera de estado */boolean estadoAbierto) {
	// TODO - implement ManejadorPuertoCOM::setEstadoAbierto
	throw "Not yet implemented";
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
	// TODO - implement ManejadorPuertoCOM::abrirManejador
	throw "Not yet implemented";
}

void ManejadorPuertoCOM::cerrarManejador() {
	// TODO - implement ManejadorPuertoCOM::cerrarManejador
	throw "Not yet implemented";
}

ManejadorPuertoCOM ManejadorPuertoCOM::recuperarInstancia() {
	// TODO - implement ManejadorPuertoCOM::recuperarInstancia
	throw "Not yet implemented";
}

HANDLE ManejadorPuertoCOM::getHandle() {
	return nullptr;
}

bool ManejadorPuertoCOM::getEstadoAbierto() {
	return this->estadoAbierto;
}
