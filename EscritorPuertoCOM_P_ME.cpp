
#include "EscritorPuertoCOM_P_ME.h"

EscritorPuertoCOM_P_ME::EscritorPuertoCOM_P_ME(ManejadorPuertoCOM *mPuertoCOM) {
	this->mPuertoCOM = mPuertoCOM;
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
