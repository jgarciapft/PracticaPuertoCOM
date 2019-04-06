#include "Principal.h"

const LPCSTR CONSTANTES::COM[] = {"COM1", "COM2", "COM3", "COM4"};
const char CONSTANTES::MSJ_SEL_COM[] = "Seleccionar el puerto a utilizar:\n1. COM1\n2. COM2\n3. COM3\n4. COM4";
const char CONSTANTES::MSJ_ERROR_SEL_COM[] = "Puerto COM incorrecto";
const DWORD CONSTANTES::VELOCIDAD_DEF = 9600;
const BYTE CONSTANTES::NUM_BITS_X_BYTE_DEF = 8;
const BYTE CONSTANTES::PARIDAD_DEF = 0;
const BYTE CONSTANTES::BITS_STOP_DEF = 0;

int main() {

	/** INICIALIZACIÓN DEL PUERTO COM */

	CargadorManejadorPuertoCOM cargadorPCOM = CargadorManejadorPuertoCOM();
	cargadorPCOM.setNombrePuerto(CONSTANTES::COM[ManejadorEntradaUsuario::preguntarRespEntRang(CONSTANTES::MSJ_SEL_COM,
																							   CONSTANTES::MSJ_ERROR_SEL_COM,
																							   1,
																							   sizeof(CONSTANTES::COM) /
																							   sizeof(LPCSTR)) - 1]);
	cargadorPCOM.setVelocidad(CONSTANTES::VELOCIDAD_DEF);
	cargadorPCOM.setNumBitsXByte(CONSTANTES::NUM_BITS_X_BYTE_DEF);
	cargadorPCOM.setParidad(CONSTANTES::PARIDAD_DEF);
	cargadorPCOM.setBitsParada(CONSTANTES::BITS_STOP_DEF);

	cargadorPCOM.inicializarManejador(); // Intenta inicializar el puerto COM con los parámetros elegidos

	/** MANEJO DE LAS OPERACIONES DEL PUERTO COM */

	// Manejador de lectura del puerto COM
	LectorPuertoCOM *lectorPuertoCOM = LectorPuertoCOM::recuperarInstancia();
	// Manejador de escritura del puerto COM
	EscritorPuertoCOM escritorPuertoCOM = EscritorPuertoCOM(ManejadorPuertoCOM::recuperarInstancia());

	while (!escritorPuertoCOM.getFinCaracter()) { // Mientras el usuario no pulse la tecla ESCAPE
		Trama *const pTrama = lectorPuertoCOM->lectura(); // Lectura del puerto COM
		if (pTrama != nullptr) {
			cout << pTrama->protoc_toString() << endl;
			delete pTrama; // HAY QUE LIBERAR MEMORIA
		}
		if (kbhit()) { // Si se ha pulsado una tecla invoca al manejador de escritura del puerto COM
			escritorPuertoCOM.escritura();
			for (auto trama : escritorPuertoCOM.getBufferTramas())
				cout << trama->protoc_toString() << endl;
			escritorPuertoCOM.liberarBufferTramas(); // HAY QUE LIBERAR MEMORIA
		}
	}

	/** CIERRE DEL PUERTO COM */

	ManejadorPuertoCOM::recuperarInstancia()->cerrarManejador();
}
