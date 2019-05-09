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
const char EscritorPuertoCOM::RUTA_DEF_FICHERO_ENVIO_ME[] = "EProtoc.txt";

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
					configuarTramaControl();
					break;
				case CONSTANTES::TECLA_F3: // Es F3
					enviarFichero(false, TD_DEF_DIRECCION);
					break;
				case CONSTANTES::TECLA_F4: // Es F4
					LectorPuertoCOM::recuperarInstancia()->setProtocoloActual(CONSTANTES::MAESTROESCLAVO);
					configurarProtocMaestroEsclavo();
					LectorPuertoCOM::recuperarInstancia()->setProtocoloActual(CONSTANTES::ESTANDAR);
					printf("%s\n", "FIN DEL PROTOCOLO MAESTRO-ESCLAVO");
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

int EscritorPuertoCOM::queTecla() {
	char primerCar = getch();

	if (manejadorTeclaEsc(primerCar))
		return 0;
	if (primerCar == CONSTANTES::TECLA_FUNCION && manejadorTeclaF5())
		return 5;

	return -1;
}

bool EscritorPuertoCOM::manejadorTeclaF5() {
	return getch() == CONSTANTES::TECLA_F5;
}

bool EscritorPuertoCOM::manejadorTeclaEsc(char teclaLeida) {
	return teclaLeida == CONSTANTES::ESCAPE;
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

void EscritorPuertoCOM::configurarProtocMaestroEsclavo() {
	// Pregunta por la identidad de la estación actual
	int identidadEstacion = ManejadorInfoUsuario::preguntarRespEntRang(
			"Seleccione la identidad de la estacion:\n\t1. Maestro\n\t2. Esclavo",
			"Modo desconocido", 1, 2);
	int selecOperacion;

	// Si se ha elegido ser el maestro, se pide la operación a realizar
	if (identidadEstacion == 1) {
		selecOperacion = ManejadorInfoUsuario::preguntarRespEntRang(
				"Seleccione operacion:\n\t1. Seleccion\n\t2. Sondeo",
				"Operacion desconocida", 1, 2);
		switch (selecOperacion) {
			case 1:
				maestro_seleccion();
				break;
			case 2:
				maestro_sondeo();
		}
	} else {
		esclavo_establecimiento();
	}
}

void EscritorPuertoCOM::maestro_seleccion() {
	NumeroCiclico genNT = NumeroCiclico(0, 1); // Generador de número de tramas
	Trama *pTrama;

	/*ESTABLECIMIENTO*/

	// El maestro inicia la comunicación pero el esclavo debe confirmaar dicho inicio de comunicación
	enviarTramaControlConResumen(Trama::llamadaSeleccion());
	pTrama = esperarTramaCompleta();
	delete pTrama;


	/* TRANSFERENCIA*/

	// El maestro enviará un fichero por tramas a la espera de la confirmación de cada una de ellas.
	// En cada inicio de etapa diferente deberemos resetear el número de trama
	enviarFichero(true, CONSTANTES::SELECCION);

	/* LIBERACIÓN */

	// El maestro liberará la comunicación directamenta porque siempre va a ser aceptada por el esclavo.

	// El maestro finaliza la comunicación
	enviarTramaControlConResumen(Trama::liberacion(CONSTANTES::SELECCION, genNT.siguiente()));
	pTrama = esperarTramaCompleta();
	delete pTrama;
}

void EscritorPuertoCOM::maestro_sondeo() {
	Trama *pTrama;
	unsigned char control;
	int respCierreCom;

	/* ESTABLECIMIENTO */

	enviarTramaControlConResumen(Trama::llamadaSondeo());
	pTrama = esperarTramaCompleta(); // Espera a que el esclavo mande la confirmación del servicio
	delete pTrama;

	/* TRANSFERENCIA */

	// Lee tramas hasta que se solicita la liberación
	do {
		// Espera una trama completa
		pTrama = esperarTramaCompleta();
		control = pTrama->getC();
		// Envía su respuesta si no es una trama de finalización
		if (control != CONSTANTES::EOT) {
			// Envía la respuesta en función de si la transmisión fue correcta
			enviarTramaControlConResumen(
					elaborarRespuesta(pTrama, LectorPuertoCOM::recuperarInstancia()->getUltimaTramaCorrecta()));
			delete pTrama;
		}
	} while (control != CONSTANTES::EOT);

	/* LIBERACIÓN */

	// Pregunta al usuario si desea terminar la comunicación, hasta que no la termine insiste
	do {
		respCierreCom = ManejadorInfoUsuario::preguntarRespEntRang("Desea terminar la comunicacion?\n\t1. Si\n\t2. No",
																   "Respuesta desconocida", 1, 2);
		switch (respCierreCom) {
			case 1:
				enviarTramaControlConResumen(Trama::confirmacionTramaN(CONSTANTES::SONDEO, pTrama->getNT()));
				break;
			case 2:
				enviarTramaControlConResumen(Trama::rechazoTramaN(CONSTANTES::SONDEO, pTrama->getNT()));
				pTrama = esperarTramaCompleta();
		}
	} while (respCierreCom != 1);
}

void EscritorPuertoCOM::esclavo_establecimiento() {
	Trama *pTrama;

	// Determinar el la operación que debe realizar el esclavo según la primera trama
	pTrama = esperarTramaCompleta();
	// Confirma la operación y llama al procedimiento específico
	enviarTramaControlConResumen(elaborarRespuesta(pTrama, true));

	// Determinación de la operación a realizar por el esclavo
	switch (pTrama->getD()) {
		case CONSTANTES::SELECCION:
			esclavo_seleccion();
			break;
		case CONSTANTES::SONDEO:
			esclavo_sondeo();
	}

	delete pTrama;
}

void EscritorPuertoCOM::esclavo_seleccion() {
	Trama *pTrama;
	unsigned char control;

	/* TRANSFERENCIA */

	// Lee tramas hasta que el maestro solicita la liberación
	do {
		// Espera una trama completa
		pTrama = esperarTramaCompleta();
		control = pTrama->getC();
		// Envía su respuesta si no es una trama de finalización
		if (control != CONSTANTES::EOT)
			// Envía la respuesta en función de si la transmisión fue correcta
			enviarTramaControlConResumen(
					elaborarRespuesta(pTrama, LectorPuertoCOM::recuperarInstancia()->getUltimaTramaCorrecta()));
	} while (control != CONSTANTES::EOT);

	/* LIBERACIÓN */

	// Al llegar a este punto, el esclavo ha recibido una trama EOT y asume el cierre de la comunicación
	enviarTramaControlConResumen(elaborarRespuesta(pTrama, true));
	delete pTrama;
}

void EscritorPuertoCOM::esclavo_sondeo() {
	NumeroCiclico genNT = NumeroCiclico(0, 1); // Generador de número de tramas
	Trama *pTrama;

	/* TRANSFERENCIA */

	enviarFichero(true, CONSTANTES::SONDEO);

	/* LIBERACIÓN */

	// Se intenta liberar la comunicación hasta que el maestro accede
	do {
		enviarTramaControlConResumen(Trama::liberacion(CONSTANTES::SONDEO, genNT.siguiente()));
		pTrama = esperarTramaCompleta();
	} while (pTrama->getC() != CONSTANTES::ACK);
	delete pTrama;
}

Trama *EscritorPuertoCOM::esperarTramaCompleta() {
	Trama *pTrama;

	do pTrama = LectorPuertoCOM::recuperarInstancia()->lectura();
	while (pTrama == nullptr);

	return pTrama;
}

bool EscritorPuertoCOM::enviarTramaDatosConConfirmacion(TramaDatos tramaDatos) {
	Trama *pTrama;
	bool esRespuestaCorrecta;
	char charSustiuido = ' ';
	int tecla;

	// Si se ha pulsado F5 se activa la bandera de introducción de error

	// Comprueba si se ha pulsado F5 para introducir un error
	if (kbhit()) {
		tecla = queTecla();
		if (tecla == 5) {
			tramaDatos.calcularBCE();
			charSustiuido = tramaDatos.sustituirPrimerCaracter();
			enviarTramaDatos(tramaDatos);
		} else if (tecla == 0) {
			return true;
		}
	} else {
		enviarTramaDatosCalculoBCE(tramaDatos); // Envía la trama de datos sin introducir errores
	}
	printf("%s\n", ManejadorInfoUsuario::resumenTrama('E', &tramaDatos).c_str());
	pTrama = esperarTramaCompleta(); // Espera la respuesta
	// Comprueba que sea respuesta correcta
	esRespuestaCorrecta = pTrama->getD() == tramaDatos.getD() && pTrama->getC() == CONSTANTES::ACK &&
						  pTrama->getNT() == tramaDatos.getNT();

	// Si ocurrió un error en la retransmisión de esta trama, se reenvia correctamente
	if (!esRespuestaCorrecta) {
		tramaDatos.restaurarPrimerCaracter(charSustiuido);
		enviarTramaDatos(tramaDatos);
		printf("%s\n", ManejadorInfoUsuario::resumenTrama('E', &tramaDatos).c_str());
		pTrama = esperarTramaCompleta(); // Espera la respuesta
	}

	delete pTrama;
	return false;
}

Trama EscritorPuertoCOM::elaborarRespuesta(Trama *pTrama, bool aceptacion) {
	return aceptacion ? Trama::confirmacionTramaN(pTrama->getD(), pTrama->getNT()) :
		   Trama::rechazoTramaN(pTrama->getD(), pTrama->getNT());
}

void EscritorPuertoCOM::enviarMensaje() {
	/** FORMATO DE MENSAJE */

	for (int i = 0; i < MSJ_NUM_CRLF; i++) { // Inserta los saltos de línea indicados
		buffer[getIdxBuffer()] = CONSTANTES::CRLN;
		setIdxBuffer(getIdxBuffer() + 1);
	}
	buffer[getIdxBuffer()] = CONSTANTES::DELIM_CAD; // Delimitador de cadena

	/** ENVÍO DE MENSAJE */

	enviarBufferTramas(buffer);
	printf("%c", CONSTANTES::CRLN); // Salta a la siguiente l?nea para seguir escribiendo

	/** REINICIO DE BANDERAS */

	setIdxBuffer(0); // Reinicia el índice del buffer de escritura
}

void EscritorPuertoCOM::enviarBufferTramasConConfirmacion(const char *buffer, unsigned char d, NumeroCiclico &genNT) {
	int idx, auxLen;

	// Divide el mensaje en las tramas necesarias mediante referencias desplazadas al puntero buffer
	for (idx = 0; idx < strlen(buffer); idx += TD_MAX_LON_DATOS) {
		auxLen = static_cast<int>(strlen(
				buffer + idx)); // Auxiliar para comprobar la longitud real de la cadena de la sección buffer + idx

		// Envía la nueva trama creada
		enviarTramaDatosConConfirmacion(TramaDatos(CONSTANTES::SINCRONISMO, d, CONSTANTES::STX, genNT.siguiente(),
												   static_cast<unsigned char>(auxLen > TD_MAX_LON_DATOS
																			  ? TD_MAX_LON_DATOS
																			  : auxLen),
												   buffer + idx));
	}
}

void EscritorPuertoCOM::enviarBufferTramas(const char *buffer) {
	int idx, auxLen;
	TramaDatos tramaDatos;

	// Divide el mensaje en las tramas necesarias mediante referencias desplazadas al puntero buffer
	for (idx = 0; idx < strlen(buffer); idx += TD_MAX_LON_DATOS) {
		auxLen = static_cast<int>(strlen(
				buffer + idx)); // Auxiliar para comprobar la longitud real de la cadena de la sección buffer + idx

		// Envía la nueva trama creada
		tramaDatos = TramaDatos(CONSTANTES::SINCRONISMO, TD_DEF_DIRECCION, TD_DEF_CONTROL,
								TD_DEF_NT,
								static_cast<unsigned char>(auxLen > TD_MAX_LON_DATOS
														   ? TD_MAX_LON_DATOS
														   : auxLen),
								buffer + idx);
		enviarTramaDatosCalculoBCE(tramaDatos);

		// Lectura de datos no exclusiva
		LectorPuertoCOM::recuperarInstancia()->lectura();
	}
}

void EscritorPuertoCOM::configuarTramaControl() {
	Trama tramaAux = Trama(); // Trama a consturir
	unsigned char C = 0; // Caracter para determinar el campo de control de la trama

	// Pregunta al usuario el tipo de trama a enviar
	switch (ManejadorInfoUsuario::preguntarRespEntRang(MSJ_SEL_TC, MSJ_ERROR_SEL_TC, 1, 4)) {
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

	tramaAux.setAttr(CONSTANTES::SINCRONISMO, TC_DEF_DIRECCION, C, TC_DEF_NT);

	// Envía la trama formada
	enviarTramaControl(tramaAux);
}

void EscritorPuertoCOM::enviarTramaControlConResumen(Trama tramaControl) {
	enviarTramaControl(tramaControl);
	printf("%s\n", ManejadorInfoUsuario::resumenTrama('E', &tramaControl).c_str());
}

void EscritorPuertoCOM::enviarTramaControl(const Trama &tramaControl) {
	HANDLE com = mPuertoCOM->getHandle();

	if (manPrtoCOMAbierto()) { // Comprueba que el puerto COM esté operativo
		EnviarCaracter(com, tramaControl.getS());
		EnviarCaracter(com, tramaControl.getD());
		EnviarCaracter(com, tramaControl.getC());
		EnviarCaracter(com, tramaControl.getNT());
	}
}

void EscritorPuertoCOM::enviarTramaDatosCalculoBCE(TramaDatos &tramaDatos) {
	// Calcula el BCE de la trama antes de enviarla
	tramaDatos.calcularBCE();
	// Envía la trama de datos
	enviarTramaDatos(tramaDatos);
}

void EscritorPuertoCOM::enviarTramaDatos(TramaDatos tramaDatos) {
	HANDLE com = ManejadorPuertoCOM::recuperarInstancia()->getHandle();

	// Envía el contenido de la trama por partes
	if (manPrtoCOMAbierto()) { // Comprueba que el puerto COM está operativo
		EnviarCaracter(com, tramaDatos.getS());
		EnviarCaracter(com, tramaDatos.getD());
		EnviarCaracter(com, tramaDatos.getC());
		EnviarCaracter(com, tramaDatos.getNT());
		EnviarCaracter(com, tramaDatos.getL());
		EnviarCadena(com, tramaDatos.getDatos(), tramaDatos.getL());
		EnviarCaracter(com, tramaDatos.getBCE());
	}
}

void EscritorPuertoCOM::enviarFichero(bool conConfirmacion, unsigned char dir) {
	HANDLE com = ManejadorPuertoCOM::recuperarInstancia()->getHandle();
	fstream fFichero; // Flujo asociado al fichero de envío del que leer el contenido a enviar
	string cabecera; // Cabecera completa del fichero. Ruta del fichero destino y autor
	string autor; // Autor del fichero
	char *cuerpoMensaje = new char[TD_MAX_LON_DATOS +
								   1]; // Auxiliar para ir almacenando cada porción del cuerpo del mensaje
	char *msjNumBytes = new char[TD_MAX_LON_DATOS + 1]; // Mensaje sobre el peso del fichero enviado
	int pesoFichero = 0; // Peso del fichero enviado. 1 char -> 1 Byte
	NumeroCiclico genNT = NumeroCiclico(0, 1);
	TramaDatos tramaDatos;

	fFichero.open(conConfirmacion ? RUTA_DEF_FICHERO_ENVIO_ME : RUTA_DEF_FICHERO_ENVIO,
				  ios::in); // Abrimos el fichero a enviar (depende de si se trabaja con o sin confirmación)
	if (fFichero.is_open()) {
		EnviarCaracter(com, CONSTANTES::CHAR_INICIO_FICHERO); // Envío de inicio de fichero

		/* LEE LA CABECERA DEL FICHERO */

		getline(fFichero, cabecera); // Lee la ruta
		cabecera.append("\n");
		getline(fFichero, autor); // Lee el autor
		autor.append("\n");
		cabecera.append(autor); // Crea una sola cadena con la cabecera

		/* ENVÍA LA CABECERA */

		// Envío con o sin confirmación de la cabecera
		if (conConfirmacion)enviarBufferTramasConConfirmacion(cabecera.c_str(), dir, genNT);
		else enviarBufferTramas(cabecera.c_str());

		printf("%s %s\n", MSJ_INICIO_ENV_FICHERO, autor.c_str());

		/* PROCESA EL CONTENIDO DEL FICHERO */

		while (!fFichero.eof()) {

			// Manejador de aborto del programa
			if (!conConfirmacion && kbhit() && queTecla() == 0) {
				setFinCaracter(true); // Activa la bandera de salida de aplicación
				break; // Salta el bucle que lee el fichero y pasa a la liberación de la comunicación
			}

			fFichero.read(cuerpoMensaje,
						  TD_MAX_LON_DATOS); // Lee una porción del tamaño de una trama de datos o hasta el EOF
			cuerpoMensaje[fFichero.gcount()] = CONSTANTES::DELIM_CAD; // Añade delimitador de cadena por seguridad

			// Comprueba que haya contenido a enviar
			if (fFichero.gcount() > 0) {
				// Envio de la trama de datos con o sin confirmación
				if (conConfirmacion) {

					bool esFin = enviarTramaDatosConConfirmacion(
							TramaDatos(CONSTANTES::SINCRONISMO, dir, CONSTANTES::STX, genNT.siguiente(),
									   static_cast<unsigned char>(fFichero.gcount()), cuerpoMensaje));
					if (esFin) {
						setFinCaracter(true);
						break;
					}
				} else {
					tramaDatos = TramaDatos(CONSTANTES::SINCRONISMO, TD_DEF_DIRECCION, TD_DEF_CONTROL,
											TD_DEF_NT,
											static_cast<unsigned char>(fFichero.gcount()),
											cuerpoMensaje);
					enviarTramaDatosCalculoBCE(tramaDatos);
				}

				// Actualización del peso del fichero
				pesoFichero += static_cast<int>(fFichero.gcount());
			}

			// Lectura de datos no exclusiva (solo si no hay confirmación)
			if (!conConfirmacion) LectorPuertoCOM::recuperarInstancia()->lectura();
		}

		EnviarCaracter(com, CONSTANTES::CHAR_FIN_FICHERO); // Envía fin de fichero
		sprintf(msjNumBytes, "%s %d %s\n", "El fichero tiene un peso de", pesoFichero, "bytes");
		// Envía el número de bytes procesados con o sin confirmación
		if (conConfirmacion)
			enviarTramaDatosConConfirmacion(
					TramaDatos(CONSTANTES::SINCRONISMO, dir, CONSTANTES::STX, genNT.siguiente(),
							   static_cast<unsigned char>(strlen(msjNumBytes)), msjNumBytes));
		else {
			tramaDatos = TramaDatos(CONSTANTES::SINCRONISMO, TD_DEF_DIRECCION, TD_DEF_CONTROL,
									TD_DEF_NT,
									static_cast<unsigned char>(strlen(msjNumBytes)), msjNumBytes);
			enviarTramaDatosCalculoBCE(tramaDatos);
		}
		// Mensaje de final de envío de fichero
		printf("%s\n", MSJ_FIN_ENV_FICHERO);
		fFichero.close(); // Cierra el fichero
	} else {
		printf("%s \n\tRuta relativa: %s\n", MSJ_ERR_FICHERO_ENVIO_NO_ENCONTRADO,
			   conConfirmacion ? RUTA_DEF_FICHERO_ENVIO_ME : MSJ_FIN_ENV_FICHERO);
	}

	delete[] msjNumBytes; // Libera la memoria asociada al mensaje del peso del fichero enviado
	delete[] cuerpoMensaje; // Libera la memoria asociada a la cadena del cuerpo del texto del fichero
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
