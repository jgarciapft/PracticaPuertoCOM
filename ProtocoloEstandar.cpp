
#include "ProtocoloEstandar.h"

ProtocoloEstandar::ProtocoloEstandar(LectorPuertoCOM *lectorPuertoCom, EscritorPuertoCOM *escritorPuertoCom)
		: Protocolo(lectorPuertoCom, escritorPuertoCom) {}

bool ProtocoloEstandar::iniciar() {
	getLectorPuertoCOM()->setProtocoloActual(CONSTANTES::ESTANDAR);
	return establecimiento();
}

bool ProtocoloEstandar::establecimiento() {
	return transmision();
}

bool ProtocoloEstandar::transmision() {
	while (!getEscritorPuertoCOM()->getFinCaracter()) { // Mientras el usuario no pulse la tecla ESCAPE
		Trama *const pTrama = getLectorPuertoCOM()->lectura(); // Lectura del puerto COM
		if (pTrama != nullptr) delete pTrama; // HAY QUE LIBERAR MEMORIA
		if (kbhit()) { // Si se ha pulsado una tecla invoca al manejador de escritura del puerto COM
			getEscritorPuertoCOM()->escritura();
			getEscritorPuertoCOM()->liberarBufferTramas(); // HAY QUE LIBERAR MEMORIA
		}
	}
	return liberacion();
}

bool ProtocoloEstandar::liberacion() {
	cout << endl << "LIBERANDO PROTOCOLO ESTANDAR" << endl;
	return true; // TODO Identificar la salida
}
