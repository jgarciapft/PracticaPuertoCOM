#include "LectorPuertoCOM.h"

const char LectorPuertoCOM::MSJ_ERROR_BCE_INVALIDO[] = "Error al recibir la trama";

LectorPuertoCOM::LectorPuertoCOM() {
	mPuertoCOM = nullptr;

	idxTrama = 1;
	tramaAux = nullptr;
}

LectorPuertoCOM::LectorPuertoCOM(ManejadorPuertoCOM *mPuertoCOM) {
	this->mPuertoCOM = mPuertoCOM;

	idxTrama = 1;
	tramaAux = nullptr;
}

void LectorPuertoCOM::lectura() {
	char car = hayContenido(); // Comprueba si hay car. Si lo hay lo lee

	if (car)
		leerTrama(car);
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
	return this->idxTrama;
}

void LectorPuertoCOM::setIdxTrama(/* Nuevo valor del índice */int idxTrama) {
	this->idxTrama = idxTrama;
}

void LectorPuertoCOM::leerTrama(char car) {
	HANDLE com = mPuertoCOM->getHandle();

	int longitud;
	char *datosRecibidos = nullptr;

	switch (getIdxTrama()) { // Determina en qué campo de la trama hay que escribir
		case 1: // Campo de Sincronismo
			tramaAux = new Trama(); // Instancia la trama base genérica
			if (car == CONSTANTES::SINCRONISMO) {
				// Detecta caracter sincronismo. Es trama
				tramaAux->setS(car);
			} else {
				printf("%s\n\tcar : %c\n", "ERROR : no es una trama", car);
				setIdxTrama(1);
			}
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
				// Procesar Trama Control (imprime la trama recibida)
				printf("%s [%s]\n", "Recibido", tramaAux->toString().c_str());
				setIdxTrama(1);
				delete tramaAux; // Destruye la trama base genérica tratada
			} else {
				unsigned char getS = tramaAux->getS();
				unsigned char getD = tramaAux->getD();
				unsigned char getC = tramaAux->getC();
				unsigned char getNT = tramaAux->getNT();

				setIdxTrama(getIdxTrama() + 1);
				delete tramaAux; // Libera la memoria asociada a la trama de datos genérica, ahora inútil
				tramaAux = new TramaDatos(getS, getD, getC, getNT, 0,
										  nullptr); // Copia de la trama genérica en una trama de datos
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
			// INSTRUMENTACIÓN DE DEPURACIÓN ->

			printf("1. SINCRONISMO : %d\n2. DIRECCION : %c\n3. CONTROL : %d\n4. NT : %c\n5. LON : %u\n",
				   tramaAux->getS(), tramaAux->getD(), tramaAux->getC(), tramaAux->getNT(),
				   dynamic_cast<TramaDatos *>(tramaAux)->getL());
			printf("MSJ recibido : %s\nBCE recibido : %u\nBCE calculado : %u\n", tramaAux->toString().c_str(), car,
				   dynamic_cast<TramaDatos *>(tramaAux)->getBCE());


			// <- INSTRUMENTACIÓN DE DEPURACIÓN
			// Procesar Trama Datos
			if (dynamic_cast<TramaDatos *>(tramaAux)->getBCE() ==
				static_cast<unsigned char>(car)) // Lo comparamos con el BCE de la trama enviada
				printf("%s", tramaAux->toString().c_str());
			else {
				printf("%s\n", MSJ_ERROR_BCE_INVALIDO);
			}
			// Reinicia las banderas de trama
			setIdxTrama(1);
			delete[] datosRecibidos; // Libera la cadena auxiliar de lectura
			delete tramaAux;
			break;
	}
}
