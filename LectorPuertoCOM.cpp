#include "LectorPuertoCOM.h"

const char LectorPuertoCOM::MSJ_ERROR_BCE_INVALIDO[] = "Error al recibir la trama";
const char LectorPuertoCOM::MSJ_ERROR_BCE_INVALIDO_FCH[] = "Error en la recepcion de la trama del fichero";
const char LectorPuertoCOM::MSJ_INICIO_REC_FICHERO[] = "Recibiendo fichero por";
const char LectorPuertoCOM::MSJ_FIN_REC_FICHERO[] = "Fichero recibido";

LectorPuertoCOM::LectorPuertoCOM() {
	mPuertoCOM = nullptr;

	idxTrama = 1;
	esTrama = false;
	recepFichero = false;
	ficheroConfigurado = 0;
	tramaAux = nullptr;
}

LectorPuertoCOM::LectorPuertoCOM(ManejadorPuertoCOM *mPuertoCOM) {
	this->mPuertoCOM = mPuertoCOM;

	idxTrama = 1;
	esTrama = false;
	recepFichero = false;
	ficheroConfigurado = 0;
	tramaAux = nullptr;
}

void LectorPuertoCOM::lectura() {
	char car = hayContenido(); // Comprueba si hay car. Si lo hay lo lee

	if (car) procesarCar(car);
}

void LectorPuertoCOM::procesarCar(/* Caracter a procesar*/char car) { // Detecta caracter sincronismo. Es trama
	if (car == CONSTANTES::SINCRONISMO || getEsTrama()) {
		leerTrama(car);
	} else {
		switch (car) {
			case EscritorPuertoCOM::CHAR_INICIO_FICHERO: // Se va a leer un fichero
				printf("%s %s\n", MSJ_INICIO_REC_FICHERO, "Autor"); // TODO extraer el autor
				setRecepFichero(true);
				setFicheroConfigurado(0);
				break;
			case EscritorPuertoCOM::CHAR_FIN_FICHERO: // Se ha terminado de leer el fichero
				printf("%s\n", MSJ_FIN_REC_FICHERO);
				setRecepFichero(false); // Reinicia la bandera de procesamiento de fichero
				break;
			default:
				printf("%s\n\tcar : %c\n", "ERROR : no es una trama", car);
		}
	}
}

void LectorPuertoCOM::leerTrama(/* Caracter de trama*/char car) {
	HANDLE com = mPuertoCOM->getHandle();

	int longitud;
	char *datosRecibidos = nullptr;

	switch (getIdxTrama()) { // Determina en qué campo de la trama hay que escribir
		case 1: // Campo de Sincronismo
			tramaAux = new Trama(); // Instancia la trama base genérica
			setEsTrama(true);

			tramaAux->setS(car);
			setIdxTrama(getIdxTrama() + 1);
			break;
		case 2: // Campo de Dirección
			tramaAux->setD(car);
			setIdxTrama(getIdxTrama() + 1);
			break;
		case 3: // Campo de Control
			tramaAux->setC(car);
			setIdxTrama(getIdxTrama() + 1);
			break;
		case 4: // Campo de Número de Trama
			tramaAux->setNT(car);

			if (tramaAux->getC() != 2) {
				// Procesar Trama Control (imprime el tipo de trama de control recibida)
				printf("%s [%s]\n", "Recibido", tramaAux->toString().c_str());
				// Reinicio de las banderas de trama
				setIdxTrama(1);
				setEsTrama(false);
				delete tramaAux; // Destruye la trama base genérica tratada
			} else {
				// Temporales para copiar los datos de la trama genérica en trama de datos
				unsigned char getS = tramaAux->getS();
				unsigned char getD = tramaAux->getD();
				unsigned char getC = tramaAux->getC();
				unsigned char getNT = tramaAux->getNT();
				delete tramaAux; // Libera la memoria asociada a la trama de datos genérica, ahora inútil

				// Copia de la trama genérica en una trama de datos
				tramaAux = new TramaDatos(getS, getD, getC, getNT, 0,
										  nullptr);
				setIdxTrama(getIdxTrama() + 1);
			}
			break;
		case 5: // Longitud
			dynamic_cast<TramaDatos *>(tramaAux)->setL(static_cast<unsigned char>(car));
		case 6: // Datos
			longitud = dynamic_cast<TramaDatos *>(tramaAux)->getL(); // Auxiliar con la longitud recibida
			datosRecibidos = new char[longitud + 1]; // Cadena auxiliar para recibir los datos (+1 para fin de cadena)

			// Recibe el mensaje
			RecibirCadena(com, datosRecibidos, longitud);
			datosRecibidos[longitud] = CONSTANTES::DELIM_CAD; // Formatea el fin de cadena por seguridad
			dynamic_cast<TramaDatos *>(tramaAux)->setDatos(datosRecibidos); // Almacena el mensaje en la trama de datos

			setIdxTrama(getIdxTrama() + 2);
			break;
		case 7:
			dynamic_cast<TramaDatos *>(tramaAux)->calcularBCE(); // Calculamos y almacenamos el BCE de nuestra trama

			// Procesar Trama Datos
			if (dynamic_cast<TramaDatos *>(tramaAux)->getBCE() ==
				static_cast<unsigned char>(car)) { // Lo comparamos con el BCE de la trama enviada
				if (getRecepFichero() && !ficheroEstaConfigurado()) { // Se está recibiendo la cabecera de un fichero
					cout << "RECIBIENDO RUTA" << endl;
					setRutaFchRecep("Frecep.txt"); // TODO Implementar
					setFicheroConfigurado(1);

					cout << "RECIBIENDO AUTOR" << endl;
					setAutorFchRecep("jgarciapft"); // TODO Implementar
					setFicheroConfigurado(2);
				} else if (getRecepFichero() &&
						   ficheroEstaConfigurado()) { // Se está recibiendo el cuerpo de un fichero
					fFichero.write(tramaAux->toString().c_str(), sizeof(tramaAux->toString().c_str()));
				} else { // Se ha recibido otra trama de datos
					printf("%s", tramaAux->toString().c_str());
				}
			} else {
				if (getRecepFichero()) printf("%s\n", MSJ_ERROR_BCE_INVALIDO_FCH);
				else printf("%s\n", MSJ_ERROR_BCE_INVALIDO);
			}
			// Reinicia las banderas de trama
			setIdxTrama(1);
			setEsTrama(false);
			delete tramaAux;
			delete[] datosRecibidos; // Libera la cadena auxiliar de lectura
			break;
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

int LectorPuertoCOM::getIdxTrama() {
	return idxTrama;
}

bool LectorPuertoCOM::getEsTrama() {
	return esTrama;
}

string LectorPuertoCOM::getAutorFchRecep() const {
	return autorFchRecep;
}

string LectorPuertoCOM::getRutaFchRecep() const {
	return rutaFchRecep;
}

bool LectorPuertoCOM::getRecepFichero() {
	return recepFichero;
}

int LectorPuertoCOM::getFicheroConfigurado() {
	return ficheroConfigurado;
}

void LectorPuertoCOM::setIdxTrama(/* Nuevo valor del índice */int idxTrama) {
	this->idxTrama = idxTrama;
}

void LectorPuertoCOM::setEsTrama(/* Nuevo valor de la bandera*/bool esTrama) {
	this->esTrama = esTrama;
}

void LectorPuertoCOM::setAutorFchRecep(/* Nuevo valor del autor*/const string &autorFchRecep) {
	this->autorFchRecep = autorFchRecep;
}

void LectorPuertoCOM::setRutaFchRecep(/* Nuevo valor de la ruta*/const string &rutaFchRecep) {
	this->rutaFchRecep = rutaFchRecep;
}

void LectorPuertoCOM::setRecepFichero(/* Nuevo valor de la bandera*/bool recepFichero) {
	this->recepFichero = recepFichero;
	if (!getRecepFichero()) {
		if (fFichero.is_open()) fFichero.close();
	}
}

void LectorPuertoCOM::setFicheroConfigurado(/* Nuevo valor de la bandera*/int ficheroConfigurado) {
	this->ficheroConfigurado = ficheroConfigurado;
	if (getRecepFichero() && ficheroEstaConfigurado()) {
		if (!fFichero.is_open())fFichero.open(getRutaFchRecep(), ios::out);
	}
}

bool LectorPuertoCOM::ficheroEstaConfigurado() {
	return getFicheroConfigurado() == 2;
}
