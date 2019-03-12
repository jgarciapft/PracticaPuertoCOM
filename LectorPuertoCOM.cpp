#include "LectorPuertoCOM.h"

LectorPuertoCOM::LectorPuertoCOM() {
	mPuertoCOM = nullptr;

	esTrama = false;
    esTramaDatos = false;
	idxTrama = 1;
    tramaAux = TramaDatos();

}

LectorPuertoCOM::LectorPuertoCOM(ManejadorPuertoCOM *mPuertoCOM) {
	this->mPuertoCOM = mPuertoCOM;

	esTrama = false;
	idxTrama = 1;
    tramaAux = TramaDatos();

}

void LectorPuertoCOM::lectura() {
	char car = hayContenido(); // Comprueba si hay car. Si lo hay lo lee

	if (car) {
		if (!getEsTrama()) { // Comprueba si está en proceso de leer una trama
			if (car == CONSTANTES::SINCRONISMO) { // Detecta caracter de sincronismo. Es trama
				setEsTrama(true);
				leerTrama(car);
			} else {
				printf("%c", car); // No es trama. Es un caracter
			}
		} else { // Está en proceso de leer una trama
			leerTrama(car);
		}
	}
}

bool LectorPuertoCOM::manPrtoCOMAbierto() {
	return mPuertoCOM != nullptr ? mPuertoCOM->getEstadoAbierto() : false;
}

char LectorPuertoCOM::hayContenido() {
	HANDLE com = mPuertoCOM->getHandle();
	// Comprueba que el manejador del puerto COM esté abierto
	return static_cast<char>(manPrtoCOMAbierto() ? RecibirCaracter(com) : 0);
}

bool LectorPuertoCOM::getEsTrama() {
	return this->esTrama;
}

bool LectorPuertoCOM::getEsTramaDatos() {
    return this->esTramaDatos;
}

int LectorPuertoCOM::getIdxTrama() {
	return this->idxTrama;
}

void LectorPuertoCOM::setEsTrama(/* Nuevo valor de la bandera */bool esTrama) {
	this->esTrama = esTrama;
}

void LectorPuertoCOM::setEsTramaDatos(bool esTramaDatos) {
    this->esTramaDatos = esTramaDatos;
}

void LectorPuertoCOM::setIdxTrama(/* Nuevo valor del índice */int idxTrama) {
	this->idxTrama = idxTrama;
}

void LectorPuertoCOM::leerTrama(char car) {
	switch (getIdxTrama()) { // Determina en qué campo de la trama hay que escribir
		case 1: // Campo de Sincronismo
			tramaAux.setS(car);
			setIdxTrama(getIdxTrama() + 1);
			break;
		case 2: // Campo de Dirección
			tramaAux.setD(car);
			setIdxTrama(getIdxTrama() + 1);
			break;
		case 3: // Campo de Control
			tramaAux.setC(car);
			setIdxTrama(getIdxTrama() + 1);
			break;
		case 4: // Campo de Número de Trama
			tramaAux.setNT(car);
            if (tramaAux.getC() != 2) {
                setIdxTrama(1);
                // Procesar Trama Control (imprime la trama recibida)
                printf("%s [%s]\n", "Recibido", ((Trama) tramaAux).toString().c_str());
            } else {
                setEsTramaDatos(true);
                setIdxTrama(getIdxTrama() + 1);
            }
            break;
        case 5:
            tramaAux.setL((unsigned char) car);
            setIdxTrama(getIdxTrama() + 1);
        case 6: // Datos
            // RecibirCadena(mPuertoCOM, tramaAux.getDatos(), tramaAux.getL());
            // Campo_Datos[Campo_Longitud] = '\0';
            setIdxTrama(getIdxTrama() + 1);
            break;
        case 7:
            tramaAux.calcularBCE();            // Calculamos y almacenamos el BCE de nuestra trama
            setIdxTrama(1);
            // Procesar Trama Datos
            if (tramaAux.getBCE() == car) {    // Lo comparamos con el BCE de la trama enviada
                printf("%s [%s]\n", "Recibido", tramaAux.toString().c_str());
            } else {
                printf("Error al recibir la trama");
            }
			// Reinicia las banderas de trama
			setEsTrama(false);
            setEsTramaDatos(false);
            break;
	}
}
