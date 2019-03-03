#include "EscritorPuertoCOM.h"

const int EscritorPuertoCOM::BUFFER_MAX_CAR = 700;
const int EscritorPuertoCOM::MSJ_NUM_CRLF = 2;
const char EscritorPuertoCOM::MSJ_SEL_TC[] = "Trama de control a enviar:\n1: Trama ENQ.\n2: Trama EOT.\n3: Trama ACK.\n4: Trama NACK.";
const char EscritorPuertoCOM::MSJ_ERROR_SEL_TC[] = "Tipo de trama incorreccta";
const unsigned char EscritorPuertoCOM::TC_DEF_DIRECCION = 'T';
const unsigned char EscritorPuertoCOM::TC_DEF_NT = '0';

EscritorPuertoCOM::EscritorPuertoCOM() {
	mPuertoCOM = nullptr;

	idxBuffer = 0;
	finCaracter = false;
}

EscritorPuertoCOM::EscritorPuertoCOM(ManejadorPuertoCOM *mPuertoCOM) {
	this->mPuertoCOM = mPuertoCOM;

	idxBuffer = 0;
	finCaracter = false;
}

void EscritorPuertoCOM::escritura() {
	char car = static_cast<char>(getch()); // Lee la tecla pulsada
	HANDLE com = mPuertoCOM->getHandle();

	switch (car) { // Determina qué tecla fue pulsada
		case CONSTANTES::ESCAPE: // ESCAPE. Fin del programa
			setFinCaracter(true);
			break;
		case CONSTANTES::TECLA_FUNCION: // TECLA FUNCIÓN
			switch (static_cast<char>(getch())) {
				case CONSTANTES::TECLA_F1: // Es F1
					for (int i = 0; i < MSJ_NUM_CRLF; i++) { // Inserta los saltos de línea indicados
						buffer[getIdxBuffer()] = CONSTANTES::CRLN;
						setIdxBuffer(getIdxBuffer() + 1);
					}
					buffer[getIdxBuffer()] = CONSTANTES::DELIM_CAD; // Delimitador de cadena

					EnviarCadena(com, buffer,
								 static_cast<int>(strlen(buffer))); // Envía el mensaje

					printf("%c", CONSTANTES::CRLN); // Salta a la siguiente línea para seguir escribiendo
					setIdxBuffer(0); // Reinicia el índice del buffer de escritura
					break;
				case CONSTANTES::TECLA_F2: // Es F2
					Trama tramaAux = Trama(); // Trama a cosnturir
					unsigned char C;

					switch (ManejadorEntradaUsuario::preguntarRespEntRang(MSJ_SEL_TC,
																		  MSJ_ERROR_SEL_TC,
																		  1,
																		  4)) {
						case 1:
							C = Trama::ENQ;
							break;
						case 2:
							C = Trama::EOT;
							break;
						case 3:
							C = Trama::ACK;
							break;
						case 4:
							C = Trama::NACK;
					}

					tramaAux.setS(CONSTANTES::SINCRONISMO);
					tramaAux.setD(TC_DEF_DIRECCION);
					tramaAux.setC(C);
					tramaAux.setNT(TC_DEF_NT);

					EnviarCaracter(com, tramaAux.getS());
					EnviarCaracter(com, tramaAux.getD());
					EnviarCaracter(com, tramaAux.getC());
					EnviarCaracter(com, tramaAux.getNT());
			}
			break;
		case CONSTANTES::TECLA_RETROCESO: // RETROCESO
			if (getIdxBuffer() > 0) { // Comprobación de no retroceder más allá del tamaño del buffer
				printf("%s", "\b \b");
				setIdxBuffer(getIdxBuffer() - 1);
			}
			break;
		default: // OTRA PULSACIÓN. Debe ser almacenada en el buffer con 'echo'
			if (!bufferLleno()) { // Comprueba que el buffer no esté lleno
				switch (car) { // Determina tratamiento del caracter a almacenar
					case CONSTANTES::TECLA_RETORNO:
						car = CONSTANTES::CRLN;
					default: // Otro caracter
						buffer[getIdxBuffer()] = car;
						setIdxBuffer(getIdxBuffer() + 1);
				}

				printf("%c", car); // 'echo' del caracter leído
			}
	}
}

bool EscritorPuertoCOM::manPrtoCOMAbierto() {
	return mPuertoCOM != nullptr ? mPuertoCOM->getEstadoAbierto() : false;
}

bool EscritorPuertoCOM::bufferLleno() { return getIdxBuffer() >= BUFFER_MAX_CAR; }

int EscritorPuertoCOM::getIdxBuffer() {
	return idxBuffer;
}

bool EscritorPuertoCOM::getFinCaracter() {
	return finCaracter;
}

void EscritorPuertoCOM::setIdxBuffer(/* Nuevo valor del índice */int idxBuffer) {
	this->idxBuffer = idxBuffer;
}

void EscritorPuertoCOM::setFinCaracter(/* Nuevo valor de la bandera */bool finCaracter) {
	this->finCaracter = finCaracter;
}
