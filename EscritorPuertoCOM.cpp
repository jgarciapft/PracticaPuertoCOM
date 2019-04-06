#include "EscritorPuertoCOM.h"

EscritorPuertoCOM *EscritorPuertoCOM::instancia = nullptr;
const int EscritorPuertoCOM::BUFFER_MAX_CAR = 700;
const int EscritorPuertoCOM::MSJ_NUM_CRLF = 1;
const char EscritorPuertoCOM::MSJ_SEL_TC[] = "Trama de control a enviar:\n1: Trama ENQ.\n2: Trama EOT.\n3: Trama ACK.\n4: Trama NACK.";
const char EscritorPuertoCOM::MSJ_ERROR_SEL_TC[] = "Tipo de trama incorrecta";
const unsigned char EscritorPuertoCOM::TC_DEF_DIRECCION = 'T';
const unsigned char EscritorPuertoCOM::TC_DEF_NT = '0';
const unsigned char EscritorPuertoCOM::TD_DEF_DIRECCION = 'T';
const unsigned char EscritorPuertoCOM::TD_DEF_CONTROL = 2;
const unsigned char EscritorPuertoCOM::TD_DEF_NT = '0';
const int EscritorPuertoCOM::TD_MAX_LON_DATOS = 254;
const char EscritorPuertoCOM::MSJ_ERR_FICHERO_ENVIO_NO_ENCONTRADO[] = "Error al abrir el fichero de envio";
const char EscritorPuertoCOM::MSJ_INICIO_ENV_FICHERO[] = "Enviando fichero por";
const char EscritorPuertoCOM::MSJ_FIN_ENV_FICHERO[] = "Fichero enviado";
const char EscritorPuertoCOM::RUTA_DEF_FICHERO_ENVIO[] = "Fenvio.txt";

EscritorPuertoCOM::EscritorPuertoCOM() {
	mPuertoCOM = ManejadorPuertoCOM::recuperarInstancia();

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
					break;
				case CONSTANTES::TECLA_F3: // Es F3
					enviarFichero();
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

void EscritorPuertoCOM::enviarMensaje() {
	/** FORMATO DE MENSAJE */

	for (int i = 0; i < MSJ_NUM_CRLF; i++) { // Inserta los saltos de línea indicados
		buffer[getIdxBuffer()] = CONSTANTES::CRLN;
		setIdxBuffer(getIdxBuffer() + 1);
	}
	buffer[getIdxBuffer()] = CONSTANTES::DELIM_CAD; // Delimitador de cadena

	/** ENVÍO DE MENSAJE */

	if (manPrtoCOMAbierto()) // Comprueba que el puerto COM esté operativo
		enviarBufferTramas(buffer);
	printf("%c", CONSTANTES::CRLN); // Salta a la siguiente línea para seguir escribiendo

	/** REINICIO DE BANDERAS */

	setIdxBuffer(0); // Reinicia el índice del buffer de escritura
}

void EscritorPuertoCOM::enviarBufferTramas(const char *bufferMsj) {
	vector<Trama *> buffAux; // Nuevo buffer de tramas enviadas
	int idx, auxLen;

	// Divide el mensaje en las tramas necesarias mediante referencias desplazadas al puntero buffer
	for (idx = 0; idx < strlen(bufferMsj); idx += TD_MAX_LON_DATOS) {
		auxLen = static_cast<int>(strlen(
				bufferMsj + idx)); // Auxiliar para comprobar la longitud real de la cadena de la sección buffer + idx

		TramaDatos *tramaDatos = new TramaDatos(CONSTANTES::SINCRONISMO, TD_DEF_DIRECCION, TD_DEF_CONTROL,
												TD_DEF_NT,
												static_cast<unsigned char>(auxLen > TD_MAX_LON_DATOS
																		   ? TD_MAX_LON_DATOS
																		   : auxLen),
												bufferMsj + idx);
		buffAux.push_back(tramaDatos); // Añade al buffer la nueva trama creada
		enviarTramaDatos(tramaDatos); // Envía la nueva trama creada

		// Lectura de datos no exclusiva
		LectorPuertoCOM::recuperarInstancia()->lectura();
	}

	setBufferTramas(buffAux); // Reasigna al buffer la trama de control enviada
}

void EscritorPuertoCOM::enviarTramaDatos(TramaDatos *tramaDatos) {
	HANDLE com = ManejadorPuertoCOM::recuperarInstancia()->getHandle();

	// Calcula el BCE de la trama antes de enviarla
	tramaDatos->calcularBCE();
	// Envía el contenido de la trama por partes
	if (manPrtoCOMAbierto()) { // Comprueba que el puerto COM esté operativo
		EnviarCaracter(com, tramaDatos->getS());
		EnviarCaracter(com, tramaDatos->getD());
		EnviarCaracter(com, tramaDatos->getC());
		EnviarCaracter(com, tramaDatos->getNT());
		EnviarCaracter(com, tramaDatos->getL());
		EnviarCadena(com, tramaDatos->getDatos(), tramaDatos->getL());
		EnviarCaracter(com, tramaDatos->getBCE());
	}
}

void EscritorPuertoCOM::enviarTramaControl() {
	HANDLE com = mPuertoCOM->getHandle();
	Trama *tramaAux = new Trama(); // Trama a consturir
	vector<Trama *> buffAux; // Nuevo buffer de tramas enviadas
	unsigned char C = 0; // Caracter para determinar el campo de control de la trama

	// Pregunta al usuario el tipo de trama a enviar
	switch (ManejadorEntradaUsuario::preguntarRespEntRang(MSJ_SEL_TC,
														  MSJ_ERROR_SEL_TC,
														  1,
														  4)) {
		case 1:
			C = CONSTANTES::ENQ;
			break;
		case 2:
			C = CONSTANTES::EOT;
			break;
		case 3:
			C = CONSTANTES::ACK;
			break;
		case 4:
			C = CONSTANTES::NACK;
	}

	tramaAux->setAttr(CONSTANTES::SINCRONISMO, TC_DEF_DIRECCION, C, TC_DEF_NT);
	buffAux.push_back(tramaAux);

	// Envía la trama formada
	if (manPrtoCOMAbierto()) { // Comprueba que el puerto COM esté operativo
		EnviarCaracter(com, tramaAux->getS());
		EnviarCaracter(com, tramaAux->getD());
		EnviarCaracter(com, tramaAux->getC());
		EnviarCaracter(com, tramaAux->getNT());

		setBufferTramas(buffAux); // Reasigna al buffer la trama de control enviada
	}
}

void EscritorPuertoCOM::enviarFichero() {
	HANDLE com = ManejadorPuertoCOM::recuperarInstancia()->getHandle();
	fstream fFichero; // Flujo asociado al fichero de envío del que leer el contenido a enviar
	string cabecera; // Cabecera completa del fichero. Ruta del fichero destino y autor
	string autor; // Autor del fichero
	char *cuerpoMensaje = new char[TD_MAX_LON_DATOS +
								   1]; // Auxiliar para ir almacenando cada porción del cuerpo del mensaje
	char *msjNumBytes = new char[TD_MAX_LON_DATOS + 1]; // Mensaje sobre el peso del fichero enviado
	int pesoFichero = 0; // Peso del fichero enviado. 1 char -> 1 Byte

	fFichero.open(RUTA_DEF_FICHERO_ENVIO, ios::in); // Abrimos el fichero a enviar
	if (fFichero.is_open()) {
		EnviarCaracter(com, CONSTANTES::CHAR_INICIO_FICHERO); // Envío de inicio de fichero

		/* LEE LA CABECERA DEL FICHERO */

		getline(fFichero, cabecera); // Lee la ruta
		cabecera.append("\n");
		getline(fFichero, autor); // Lee el autor
		autor.append("\n");
		cabecera.append(autor); // Crea una sola cadena con la cabecera

		/* ENVÍA LA CABECERA */

		enviarBufferTramas(cabecera.c_str());
		printf("%s %s\n", MSJ_INICIO_ENV_FICHERO, autor.c_str());

		/* PROCESA EL CONTENIDO DEL FICHERO */

		while (!fFichero.eof()) {
			fFichero.read(cuerpoMensaje,
						  TD_MAX_LON_DATOS); // Lee una porción del tamaño de una trama de datos o hasta el EOF
			cuerpoMensaje[fFichero.gcount()] = CONSTANTES::DELIM_CAD; // Añade delimitador de cadena por seguridad

			// Comprueba que haya contenido a enviar
			if (fFichero.gcount() > 0) {
				// Envio de la trama de datos
				enviarTramaDatos(new TramaDatos(CONSTANTES::SINCRONISMO, TD_DEF_DIRECCION, TD_DEF_CONTROL, TD_DEF_NT,
												static_cast<unsigned char>(fFichero.gcount()), cuerpoMensaje));
				// Actualización del peso del fichero
				pesoFichero += static_cast<int>(fFichero.gcount());
			}

			// Lectura de datos no exclusiva
			LectorPuertoCOM::recuperarInstancia()->lectura();
		}

		EnviarCaracter(com, CONSTANTES::CHAR_FIN_FICHERO); // Envía fin de fichero
		// Envía el número de bytes procesados
		sprintf(msjNumBytes, "%s %d %s\n", "El fichero tiene un peso de", pesoFichero, "bytes");
		enviarTramaDatos(new TramaDatos(CONSTANTES::SINCRONISMO, TD_DEF_DIRECCION, TD_DEF_CONTROL, TD_DEF_NT,
										static_cast<unsigned char>(strlen(msjNumBytes)), msjNumBytes));
		// Mensaje de final de envío de fichero
		printf("%s\n", MSJ_FIN_ENV_FICHERO);
		fFichero.close(); // Cierra el fichero
	} else {
		printf("%s \n\tRuta relativa: %s\n", MSJ_ERR_FICHERO_ENVIO_NO_ENCONTRADO, RUTA_DEF_FICHERO_ENVIO);
	}

	delete[] msjNumBytes; // Libera la memoria asociada al mensaje del peso del fichero enviado
	delete[] cuerpoMensaje; // Libera la memoria asociada a la cadena del cuerpo del texto del fichero
}

bool EscritorPuertoCOM::manPrtoCOMAbierto() {
	return mPuertoCOM != nullptr ? mPuertoCOM->getEstadoAbierto() : false;
}

bool EscritorPuertoCOM::bufferLleno() { return getIdxBuffer() >= BUFFER_MAX_CAR; }

vector<Trama *> EscritorPuertoCOM::getBufferTramas() {
	return bufferTramas;
}

void EscritorPuertoCOM::liberarBufferTramas() {
	auto inicio = std::stable_partition(bufferTramas.begin(), bufferTramas.end(),
										[](Trama *trama) { return true; });
	std::for_each(inicio, bufferTramas.end(), [](Trama *trama) { delete trama; });
	bufferTramas.erase(inicio, bufferTramas.end());
}

int EscritorPuertoCOM::getIdxBuffer() {
	return idxBuffer;
}

bool EscritorPuertoCOM::getFinCaracter() {
	return finCaracter;
}

void EscritorPuertoCOM::setBufferTramas(vector<Trama *> bufferTramas) {
	this->bufferTramas = bufferTramas;
}

void EscritorPuertoCOM::setIdxBuffer(int idxBuffer) {
	this->idxBuffer = idxBuffer;
}

void EscritorPuertoCOM::setFinCaracter(bool finCaracter) {
	this->finCaracter = finCaracter;
}

EscritorPuertoCOM::~EscritorPuertoCOM() {
	// Libera el buffer de escritura
	delete[] buffer;
}

EscritorPuertoCOM *EscritorPuertoCOM::recuperarInstancia() {
	if (instancia == nullptr)
		instancia = new EscritorPuertoCOM();

	return instancia;
}
