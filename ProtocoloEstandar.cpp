
#include "ProtocoloEstandar.h"

ProtocoloEstandar::ProtocoloEstandar(LectorPuertoCOM *lectorPuertoCom, EscritorPuertoCOM *escritorPuertoCom)
		: Protocolo(lectorPuertoCom, escritorPuertoCom) {}

void ProtocoloEstandar::iniciar() {
	establecimiento();
}

void ProtocoloEstandar::establecimiento() {
	transmision();
}

void ProtocoloEstandar::transmision() {
	while (!getEscritorPuertoCOM()->getFinCaracter()) { // Mientras el usuario no pulse la tecla ESCAPE
		Trama *const pTrama = getLectorPuertoCOM()->lectura(); // Lectura del puerto COM
		if (pTrama != nullptr) delete pTrama; // HAY QUE LIBERAR MEMORIA
		if (kbhit()) { // Si se ha pulsado una tecla invoca al manejador de escritura del puerto COM
			getEscritorPuertoCOM()->escritura();
			getEscritorPuertoCOM()->liberarBufferTramas(); // HAY QUE LIBERAR MEMORIA
		}
	}
	liberacion(true);
}

bool ProtocoloEstandar::liberacion(bool finAplicacion) {
	cout << "LIBERANDO PROTOCOLO ESTANDAR";
	return finAplicacion;
}
