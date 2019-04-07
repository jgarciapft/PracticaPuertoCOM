#include "Principal.h"

const LPCSTR Principal::COM[] = {"COM1", "COM2", "COM3", "COM4"};
const char Principal::MSJ_SEL_COM[] = "Seleccionar el puerto a utilizar:\n1. COM1\n2. COM2\n3. COM3\n4. COM4";
const char Principal::MSJ_ERROR_SEL_COM[] = "Puerto COM incorrecto";
const DWORD Principal::VELOCIDAD_DEF = 9600;
const BYTE Principal::NUM_BITS_X_BYTE_DEF = 8;
const BYTE Principal::PARIDAD_DEF = 0;
const BYTE Principal::BITS_STOP_DEF = 0;

int main() {

	/** INICIALIZACIÓN DEL PUERTO COM */

	CargadorManejadorPuertoCOM cargadorPCOM = CargadorManejadorPuertoCOM();
	cargadorPCOM.setNombrePuerto(Principal::COM[ManejadorEntradaUsuario::preguntarRespEntRang(Principal::MSJ_SEL_COM,
																							  Principal::MSJ_ERROR_SEL_COM,
																							  1,
																							  sizeof(Principal::COM) /
																							  sizeof(LPCSTR)) - 1]);
	cargadorPCOM.setVelocidad(Principal::VELOCIDAD_DEF);
	cargadorPCOM.setNumBitsXByte(Principal::NUM_BITS_X_BYTE_DEF);
	cargadorPCOM.setParidad(Principal::PARIDAD_DEF);
	cargadorPCOM.setBitsParada(Principal::BITS_STOP_DEF);

	cargadorPCOM.inicializarManejador(); // Intenta inicializar el puerto COM con los parámetros elegidos

	/** MANEJO DE LAS OPERACIONES DEL PUERTO COM */

	// Manejador del control de los protocolos de aplicación. Maneja el resto del flujo del programa
	ManejadorProtocolo().ejecutar();

	/** CIERRE DEL PUERTO COM */

	ManejadorPuertoCOM::recuperarInstancia()->cerrarManejador();
}
