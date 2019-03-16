#include "EscritorPuertoCOM.h"

const int EscritorPuertoCOM::BUFFER_MAX_CAR = 700;
const int EscritorPuertoCOM::MSJ_NUM_CRLF = 2;
const char EscritorPuertoCOM::MSJ_SEL_TC[] = "Trama de control a enviar:\n1: Trama ENQ.\n2: Trama EOT.\n3: Trama ACK.\n4: Trama NACK.";
const char EscritorPuertoCOM::MSJ_ERROR_SEL_TC[] = "Tipo de trama incorrecta";
const unsigned char EscritorPuertoCOM::TC_DEF_DIRECCION = 'T';
const unsigned char EscritorPuertoCOM::TC_DEF_NT = '0';
const unsigned char EscritorPuertoCOM::TD_DEF_DIRECCION = 'T';
const unsigned char EscritorPuertoCOM::TD_DEF_CONTROL = 2;
const unsigned char EscritorPuertoCOM::TD_DEF_NT = '0';

EscritorPuertoCOM::EscritorPuertoCOM() {
	mPuertoCOM = nullptr;

	// Reserva el espacio necesario para el buffer de escritura
	buffer = new char[BUFFER_MAX_CAR + MSJ_NUM_CRLF + 1];
	idxBuffer = 0;
	finCaracter = false;
}

EscritorPuertoCOM::EscritorPuertoCOM(ManejadorPuertoCOM *mPuertoCOM) {
	this->mPuertoCOM = mPuertoCOM;

	// Reserva el espacio necesario para el buffer de escritura
	buffer = new char[BUFFER_MAX_CAR + MSJ_NUM_CRLF + 1];
	idxBuffer = 0;
	finCaracter = false;
}

void EscritorPuertoCOM::escritura() {
	char car = static_cast<char>(getch()); // Lee la tecla pulsada

	switch (car) { // Determina qué tecla fue pulsada
		case CONSTANTES::ESCAPE: // ESCAPE. Fin del programa
			setFinCaracter(true);
			break;
		case CONSTANTES::TECLA_FUNCION: // TECLA FUNCIÓN
			switch (static_cast<char>(getch())) {
				case CONSTANTES::TECLA_F1: // Es F1
					enviarMensaje();
					break;
				case CONSTANTES::TECLA_F2: // Es F2
					enviarTramaControl();
			}
			break;
		case CONSTANTES::TECLA_RETROCESO: // RETROCESO
			if (getIdxBuffer() > 0) { // Comprobación de no retroceder más allá del tamaño del buffer
				printf("%s", "\b \b");
				setIdxBuffer(getIdxBuffer() - 1);
			}
			break;
		default: // OTRA PULSACIÓN. Debe ser almacenada en el buffer con 'echo'
			leerCarEcho(car);
	}
}

void EscritorPuertoCOM::enviarMensaje() {
	/** FORMATO DE MENSAJE */

	for (int i = 0; i < MSJ_NUM_CRLF; i++) { // Inserta los saltos de línea indicados
		buffer[getIdxBuffer()] = CONSTANTES::CRLN;
		setIdxBuffer(getIdxBuffer() + 1);
	}
	buffer[getIdxBuffer()] = CONSTANTES::DELIM_CAD; // Delimitador de cadena

	/** ENVÍO DE MENSAJE */

	if (manPrtoCOMAbierto()) // Comprueba que el puerto COM esté operativo
		enviarBufferTramas();
	printf("%c", CONSTANTES::CRLN); // Salta a la siguiente línea para seguir escribiendo

	/** REINICIO DE BANDERAS */

	setIdxBuffer(0); // Reinicia el índice del buffer de escritura
}

void EscritorPuertoCOM::enviarBufferTramas() {
	int idx, auxLen;
	TramaDatos tramaDatos;

	// Divide el mensaje en las tramas necesarias mediante referencias desplazadas al puntero buffer
	for (idx = 0; idx < strlen(buffer); idx += 254) {
		auxLen = static_cast<int>(strlen(
				buffer + idx)); // Auxiliar para comprobar la longitud real de la cadena de la sección buffer + idx

		tramaDatos = TramaDatos(CONSTANTES::SINCRONISMO, TD_DEF_DIRECCION, TD_DEF_CONTROL, TD_DEF_NT,
								static_cast<unsigned char>(auxLen > 254 ? 254 : auxLen), buffer + idx);

		tramaDatos.calcularBCE(); // Calcula el BCE la trama antes de enviarla
		enviarTramaDatos(tramaDatos);
	}
}

void EscritorPuertoCOM::enviarTramaDatos(TramaDatos tramaDatos) {
	HANDLE com = ManejadorPuertoCOM::recuperarInstancia()->getHandle();

	// Envía el contenido de la trama por partes
	EnviarCaracter(com, tramaDatos.getS());
	EnviarCaracter(com, tramaDatos.getD());
	EnviarCaracter(com, tramaDatos.getC());
	EnviarCaracter(com, tramaDatos.getNT());
	EnviarCaracter(com, tramaDatos.getL());
	EnviarCadena(com, tramaDatos.getDatos(), tramaDatos.getL());
	EnviarCaracter(com, CONSTANTES::DELIM_CAD); // Envía el fin de cadena '\0'
	EnviarCaracter(com, tramaDatos.getBCE());
}

void EscritorPuertoCOM::enviarTramaControl() {
	HANDLE com = mPuertoCOM->getHandle();
	Trama tramaAux = Trama(); // Trama a cosnturir
	unsigned char C; // Caracter para determinar el campo de control de la trama

	// Pregunta al usuario el tipo de trama a enviar
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

	tramaAux.setAttr(CONSTANTES::SINCRONISMO, TC_DEF_DIRECCION, C, TC_DEF_NT);

	// Envía la trama formada
	if (manPrtoCOMAbierto()) { // Comprueba que el puerto COM esté operativo
		EnviarCaracter(com, tramaAux.getS());
		EnviarCaracter(com, tramaAux.getD());
		EnviarCaracter(com, tramaAux.getC());
		EnviarCaracter(com, tramaAux.getNT());
	}
}

void EscritorPuertoCOM::leerCarEcho(char car) {
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

EscritorPuertoCOM::~EscritorPuertoCOM() {
	// Libera el buffer de escritura
	delete[] buffer;
}
