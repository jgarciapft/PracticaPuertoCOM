
#include "EscritorPuertoCOM_P_ME.h"

EscritorPuertoCOM_P_ME::EscritorPuertoCOM_P_ME(ManejadorPuertoCOM *mPuertoCOM) {
	this->mPuertoCOM = mPuertoCOM;
}

void EscritorPuertoCOM_P_ME::enviarTramaDatos(TramaDatos tramaDatos) {
	HANDLE com = ManejadorPuertoCOM::recuperarInstancia()->getHandle();

	// Calcula el BCE de la trama antes de enviarla
	tramaDatos.calcularBCE();
	// Envía el contenido de la trama por partes
	if (manPrtoCOMAbierto()) { // Comprueba que el puerto COM esté operativo
		EnviarCaracter(com, tramaDatos.getS());
		EnviarCaracter(com, tramaDatos.getD());
		EnviarCaracter(com, tramaDatos.getC());
		EnviarCaracter(com, tramaDatos.getNT());
		EnviarCaracter(com, tramaDatos.getL());
		EnviarCadena(com, tramaDatos.getDatos(), tramaDatos.getL());
		EnviarCaracter(com, tramaDatos.getBCE());
	}
}

void EscritorPuertoCOM_P_ME::enviarTramaControl(Trama tramaControl) {
	HANDLE com = mPuertoCOM->getHandle();

	// Envía la trama formada
	if (manPrtoCOMAbierto()) { // Comprueba que el puerto COM esté operativo
		EnviarCaracter(com, tramaControl.getS());
		EnviarCaracter(com, tramaControl.getD());
		EnviarCaracter(com, tramaControl.getC());
		EnviarCaracter(com, tramaControl.getNT());
	}
}

bool EscritorPuertoCOM_P_ME::manPrtoCOMAbierto() {
	return mPuertoCOM != nullptr ? mPuertoCOM->getEstadoAbierto() : false;
}

void EscritorPuertoCOM_P_ME::liberarBufferTramas() {
	vector<Trama *> buffVacio;
	auto inicio = stable_partition(bufferTramas.begin(), bufferTramas.end(),
								   [](Trama *trama) { return true; });
	for_each(inicio, bufferTramas.end(), [](Trama *trama) { delete trama; });
	bufferTramas.erase(inicio, bufferTramas.end());
	setBufferTramas(buffVacio);
}

vector<Trama *> EscritorPuertoCOM_P_ME::getBufferTramas() {
	return bufferTramas;
}

void EscritorPuertoCOM_P_ME::setBufferTramas(vector<Trama *> bufferTramas) {
	this->bufferTramas = bufferTramas;
}
