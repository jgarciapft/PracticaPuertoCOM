//============================================================================
// ----------- PRÁCTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2018/19 --------------------------------
// ----------------------------- SESION1.CPP ---------------------------------
//============================================================================

/// @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include "PuertoSerie.h"

using namespace std;

HANDLE PuertoCOM;                                // Manejador del puerto COM global

int main() {

	/*	CONSTANTES	*/

	// Mensaje para mostrar las opciones de seleccionar un puerto COM
	const char MSJ_SEL_COM[] = "Seleccionar el puerto a utilizar:\n1. COM1\n2. COM2\n3. COM3\n4. COM4";
	// Mensaje para indicar opción inválida en la elección de puerto COM
	const char MSJ_ERROR_SEL_COM[] = "Puerto COM incorrecto";
	// Colección de constantes de cadenas puerto COM
	const string COM[] = {"COM1", "COM2", "COM3", "COM4"};
	const int MAX_CAR_BUFFERESC = 700;            // Número máximo de caracteres del buffer de cadena a enviar
	const int NUM_FINLINEA = 2;                    // Número de caracteres fin de línea a insertar al final de la cadena

	/*	VARIABLES LOCALES	*/

	bool selCOMCorrecta = false;                // Bandera de selección correcta de puerto COM
	char *cadPuertoCOM = new char;                // Cadena auxiliar para leer la entrada de usuario
	int nPuertoCOM;                                // Número de puerto COM elejido por el usuario

	char bufferEsc[MAX_CAR_BUFFERESC + NUM_FINLINEA + 1];    // Buffer de escritura
	int iBufferEsc = 0;                            // Índice del buffer de escritura
	char car = 0;                                // Auxiliar para leer / escribir caracteres del / al puerto COM



	// Manejador de selección del puerto COM
	do {
		printf("%s\n\n", MSJ_SEL_COM);            // Muestra el mensaje de selección de puerto COM
		cin >> cadPuertoCOM;                    // Lee la entrada de usuario
		nPuertoCOM = strtol(cadPuertoCOM, nullptr, 10);    // Intenta convertir a número la entrada de usuario

		if (nPuertoCOM >= 1 && nPuertoCOM <= 4)            // Control de opción
			selCOMCorrecta = true;
		else                                    // Opción inválida. Se muestra msj error y se vuelve a leer opción
			printf("%s (%s)\n", MSJ_ERROR_SEL_COM, cadPuertoCOM);
	} while (!selCOMCorrecta);

	// Inicializa el HANDLE del pueto COM. Por defecto se selecciona el COM1
	// Parámetros necesarios al llamar a AbrirPuerto:
	// - Nombre del puerto a abrir ("COM1", "COM2", "COM3", ...).
	// - Velocidad (1200, 1400, 4800, 9600, 19200, 38400, 57600, 115200).
	// - Número de bits en cada byte enviado o recibido (4, 5, 6, 7, 8).
	// - Paridad (0=sin paridad, 1=impar, 2=par, 3=marca, 4=espacio).
	// - Bits de stop (0=1 bit, 1=1.5 bits, 2=2 bits)
	PuertoCOM = AbrirPuerto(COM[nPuertoCOM - 1].c_str(), 9600, 8, 0, 0);
	// Comprueba que el puerto esté operativo
	if (PuertoCOM == nullptr) {
		printf("Error al abrir el puerto\n");
		getch();
		return (1);
	} else
		printf("Puerto abierto correctamente\n");

	// Lectura y escritura simultánea de caracteres:
	while (car != 27) {
		car = RecibirCaracter(PuertoCOM);
		if (car)
			printf("%c", car);                    //Recepción
		if (kbhit()) {                            // Envío
			car = getch();                        // Lee la tecla pulsada
			switch (car) {
				case 27:                        // ESCAPE
					break;
				case '\0':                        // Es tecla de función
					if (getch() == 59) {        // ENVIAR
						if (iBufferEsc > 0) {        // Comprueba que el mensaje tenga contenido
							for (int i = 0; i < NUM_FINLINEA; i++) {    // Inserta los saltos de línea indicados
								bufferEsc[iBufferEsc] = '\n';
								iBufferEsc++;
							}
							bufferEsc[iBufferEsc] = '\0';                // Delimitador de cadena
							EnviarCadena(PuertoCOM, bufferEsc,
										 static_cast<int>(strlen(bufferEsc)));    // Envía el mensaje
							printf("%c", '\n');        // Salta a la siguiente línea para seguir escribiendo
							iBufferEsc = 0;            // Reinicia el índice del buffer de escritura
						}
					}
					break;
				case '\b':                        // BORRADO
					if (iBufferEsc > 0) {        // Comprobación de no retroceder más allá del tamaño del buffer
						printf("%c", '\b');
						printf("%c", ' ');
						printf("%c", '\b');
						iBufferEsc--;
					}
					break;
				default:                        // OTRA PULSACION. Debe hacerse ECHO
					if (iBufferEsc < MAX_CAR_BUFFERESC) {            // Control de longitud máxima de la cadena a enviar
						switch (car) {            // Determinación de otra pulsación
							case 13:            // RETORNO DEL CARRO
								printf("%c", '\n');                    // Echo de la nueva línea
								bufferEsc[iBufferEsc] = '\n';        // Escritura en el buffer de la nueva línea
								break;
							default:            // OTRA PULSACIÓN
								bufferEsc[iBufferEsc] = car;        // Escritura en el buffer del nuevo caracter
								printf("%c", car);                    // Echo del nuevo caracter
						}
						iBufferEsc++;
					}
			}
		}
	}

	// Para cerrar el puerto:
	CerrarPuerto(PuertoCOM);

	return 0;
}
