
#include "ManejadorProtocolo.h"

ManejadorProtocolo::ManejadorProtocolo() {
	protocoloEstandar = new ProtocoloEstandar(LectorPuertoCOM::recuperarInstancia(),
											  EscritorPuertoCOM::recuperarInstancia());
//	protocoloMaestroEsclavo = new ProtocoloEstandar(lectorPuertoCOM, EscritorPuertoCOM); TODO Instanciar

	protocoloActual = const_cast<Protocolo *>(protocoloEstandar);
}

ManejadorProtocolo::~ManejadorProtocolo() {
	delete protocoloEstandar;
//	delete protocoloMaestroEsclavo; TODO Quitar cuando haya sido instanciado
	delete LectorPuertoCOM::recuperarInstancia();
	delete EscritorPuertoCOM::recuperarInstancia();
}

void ManejadorProtocolo::ejecutar() {
	while (!getProtocoloActual()->iniciar())
		cambiarProtocoloActual();
	cout << "FIN APLICACION";
}

Protocolo *ManejadorProtocolo::getProtocoloActual() {
	return protocoloActual;
}

void ManejadorProtocolo::cambiarProtocoloActual() {
	this->protocoloActual = const_cast<Protocolo *>(getProtocoloActual() == protocoloEstandar ? protocoloMaestroEsclavo
																							  : protocoloEstandar);
}
