
#include "ManejadorProtocolo.h"
#include "ProtocoloEstandar.h"

ManejadorProtocolo::ManejadorProtocolo(LectorPuertoCOM *lectorPuertoCOM, EscritorPuertoCOM *EscritorPuertoCOM) {
	protocoloEstandar = new ProtocoloEstandar(lectorPuertoCOM, EscritorPuertoCOM);
//	protocoloMaestroEsclavo = new ProtocoloEstandar(lectorPuertoCOM, EscritorPuertoCOM); TODO Instanciar

	protocoloActual = const_cast<Protocolo *>(protocoloEstandar);
}

ManejadorProtocolo::~ManejadorProtocolo() {
	delete protocoloEstandar;
//	delete protocoloMaestroEsclavo; TODO Quitar cuando haya sido instanciado
}

void ManejadorProtocolo::ejecutar() {
	while (!getProtocoloActual()->iniciar())
		setProtocoloActual(const_cast<Protocolo *>(getProtocoloActual() == protocoloEstandar ? protocoloMaestroEsclavo
																							 : protocoloEstandar));
	cout << "FIN APLICACION";
}

Protocolo *ManejadorProtocolo::getProtocoloActual() {
	return protocoloActual;
}

void ManejadorProtocolo::setProtocoloActual(Protocolo *protocoloActual) {
	this->protocoloActual = protocoloActual;
}
