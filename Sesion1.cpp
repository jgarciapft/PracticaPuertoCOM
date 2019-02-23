//============================================================================
// ----------- PR�CTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2018/19 --------------------------------
// ----------------------------- SESION1.CPP ---------------------------------
//============================================================================

/// @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
/// @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include "PuertoSerie.h"

using namespace std;

HANDLE PuertoCOM;                                // Manejador del puerto COM global

struct TramaControl {
	unsigned char S;                // Sincronismo
	unsigned char D;                // Direcci�n
	unsigned char C;                // Control
	unsigned char NT;                // N�mero de trama
};

int main() {

	/*	CONSTANTES	*/

	// Mensaje para mostrar las opciones de seleccionar un puerto COM
	const char MSJ_SEL_COM[] = "Seleccionar el puerto a utilizar:\n1. COM1\n2. COM2\n3. COM3\n4. COM4";
	//Mensaje para mostrar las opciones de seleccionar tipo de trama de control
	const char MSJ_SEL_TC[] = "Trama de control a enviar:\n1: Trama ENQ.\n2: Trama EOT.\n3: Trama ACK.\n4: Trama NACK.";
	// Mensaje para indicar opci�n inv�lida en la elecci�n de puerto COM
	const char MSJ_ERROR_SEL_COM[] = "Puerto COM incorrecto";
	// Mensaje para indicar opci�n inv�lida en la elecci�n de tipo de trama de control
	const char MSJ_ERROR_SEL_TC[] = "Tipo de trama incorreccta";
	// Colecci�n de constantes de cadenas puerto COM
	const string COM[] = {"COM1", "COM2", "COM3", "COM4"};
	// Colecci�n de identificadores de tipos de TC
	const string tiposTC[] = {"ENQ", "EOT", "ACK", "NACK"};
	// Colecci�n de c�digos ASCII de cada tipo de TC
	const unsigned char codTiposTC[] = {5, 4, 6, 21};
	const int MAX_CAR_BUFFERESC = 700;            // N�mero m�ximo de caracteres del buffer de cadena a enviar
	const int NUM_SALTOLINEA = 2;                    // N�mero de caracteres de salto de l�nea a insertar al final de la cadena

	/*	VARIABLES LOCALES	*/

	bool selCOMCorrecta = false;                // Bandera de selecci�n correcta de puerto COM
	bool selTipoTCCorrecta = false;                    // Bandera de selecci�n correcta del tipo de TC
	char *cadPuertoCOM = new char;                // Cadena auxiliar para leer la entrada de usuario
	char *cadTipoTC = new char;                    // Cadena auxiliar para leer la entrada de usuario
	int nPuertoCOM;                                // N�mero de puerto COM elegido por el usuario
	int nTipoTC;                                // N�mero de opci�n de TR elegida por el usuario
	int campo = 1;                                    // �ndice de campo TR le�do
	TramaControl TRAux;                            // Trama de control auxiliar

	char bufferEsc[MAX_CAR_BUFFERESC + NUM_SALTOLINEA + 1];    // Buffer de escritura
	int iBufferEsc = 0;                            // �ndice del buffer de escritura
	char car = 0;                                // Auxiliar para leer / escribir caracteres del / al puerto COM



	// Manejador de selecci�n del puerto COM
	do {
		printf("%s\n\n", MSJ_SEL_COM);            // Muestra el mensaje de selecci�n de puerto COM
		cin >> cadPuertoCOM;                    // Lee la entrada de usuario
		nPuertoCOM = strtol(cadPuertoCOM, nullptr, 10);    // Intenta convertir a n�mero la entrada de usuario

		if (nPuertoCOM >= 1 && nPuertoCOM <= 4)            // Control de opci�n
			selCOMCorrecta = true;
		else                                    // Opci�n inv�lida. Se muestra msj error y se vuelve a leer opci�n
			printf("%s (%s)\n", MSJ_ERROR_SEL_COM, cadPuertoCOM);
	} while (!selCOMCorrecta);

	// Inicializa el HANDLE del pueto COM. Por defecto se selecciona el COM1
	// Par�metros necesarios al llamar a AbrirPuerto:
	// - Nombre del puerto a abrir ("COM1", "COM2", "COM3", ...).
	// - Velocidad (1200, 1400, 4800, 9600, 19200, 38400, 57600, 115200).
	// - N�mero de bits en cada byte enviado o recibido (4, 5, 6, 7, 8).
	// - Paridad (0=sin paridad, 1=impar, 2=par, 3=marca, 4=espacio).
	// - Bits de stop (0=1 bit, 1=1.5 bits, 2=2 bits)
	PuertoCOM = AbrirPuerto(COM[nPuertoCOM - 1].c_str(), 9600, 8, 0, 0);
	// Comprueba que el puerto est� operativo
	if (PuertoCOM == nullptr) {
		printf("Error al abrir el puerto\n");
		getch();
		return (1);
	} else
		printf("Puerto abierto correctamente\n");

	// Lectura y escritura simult�nea de caracteres:
	while (car != 27) {
		car = RecibirCaracter(PuertoCOM);
		if (car) {
			switch (campo) {
				case 1:
					if (car == 22) {                // Detecta caracter de sincronismo. Es trama
						TRAux.S = static_cast<unsigned char>(car);
						campo++;
					} else {                        // No es trama
						printf("%c", car);
					}
					break;
				case 2:
					TRAux.D = static_cast<unsigned char>(car);
					campo++;
					break;
				case 3:
					TRAux.C = static_cast<unsigned char>(car);
					campo++;
					break;
				case 4:
					TRAux.NT = static_cast<unsigned char>(car);
					printf("%s %s\n\n", "Se ha recibido una trama de control", tiposTC[TRAux.C - 1].c_str());
					campo = 1;
					break;
				default:
					break;
			}
		}                    //Recepci�n
		if (kbhit()) {                            // Env�o
			car = static_cast<char>(getch());         // Lee la tecla pulsada
			switch (car) {
				case 27:                        // ESCAPE
					break;
				case '\0':                        // Es tecla de funci�n
					switch (getch()) {        // ENVIAR
						case 59:                    // F1
							if (iBufferEsc > 0) {        // Comprueba que el mensaje tenga contenido
								for (int i = 0; i < NUM_SALTOLINEA; i++) {    // Inserta los saltos de l�nea indicados
									bufferEsc[iBufferEsc] = '\n';
									iBufferEsc++;
								}
								bufferEsc[iBufferEsc] = '\0';                // Delimitador de cadena
								EnviarCadena(PuertoCOM, bufferEsc,
											 static_cast<int>(strlen(bufferEsc)));    // Env�a el mensaje
								printf("%c", '\n');        // Salta a la siguiente l�nea para seguir escribiendo
								iBufferEsc = 0;            // Reinicia el �ndice del buffer de escritura
							}
							break;
						case 60:                    // F2
							// Manejador de selecci�n del tipo de TC
							do {
								printf("%s\n\n",
									   MSJ_SEL_TC);            // Muestra el mensaje de selecci�n de tipo de TC
								cin >> cadTipoTC;                    // Lee la entrada de usuario
								nTipoTC = strtol(cadTipoTC, nullptr,
												 10);    // Intenta convertir a n�mero la entrada de usuario

								if (nTipoTC >= 1 && nTipoTC <= 4)            // Control de opci�n
									selTipoTCCorrecta = true;
								else                                    // Opci�n inv�lida. Se muestra msj error y se vuelve a leer opci�n
									printf("%s (%s)\n", MSJ_ERROR_SEL_TC, cadTipoTC);
							} while (!selTipoTCCorrecta);

							TramaControl tramaControl{22, 'T', codTiposTC[nTipoTC - 1], '0'};

							EnviarCaracter(PuertoCOM, tramaControl.S);
							EnviarCaracter(PuertoCOM, tramaControl.D);
							EnviarCaracter(PuertoCOM, tramaControl.C);
							EnviarCaracter(PuertoCOM, tramaControl.NT);
							break;
					}
					break;
				case '\b':                        // BORRADO
					if (iBufferEsc > 0) {        // Comprobaci�n de no retroceder m�s all� del tama�o del buffer
						printf("%s", "\b \b");
						iBufferEsc--;
					}
					break;
				default:                        // OTRA PULSACION. Debe hacerse ECHO
					if (iBufferEsc < MAX_CAR_BUFFERESC) {            // Control de longitud m�xima de la cadena a enviar
						switch (car) {            // Determinaci�n de otra pulsaci�n
							case 13:            // RETORNO DEL CARRO
								bufferEsc[iBufferEsc] = '\n';        // Escritura en el buffer de la nueva l�nea
								printf("%c", '\n');                    // Echo de la nueva l�nea
								break;
							default:            // OTRA PULSACI�N
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
