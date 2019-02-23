//============================================================================
// ----------- PRÁCTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2018/19 --------------------------------
// ----------------------------- SESION1.CPP ---------------------------------
//============================================================================


#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include "PuertoSerie.h"

using namespace std;

HANDLE PuertoCOM;

int main() {
	char car = 0;

// Parámetros necesarios al llamar a AbrirPuerto:
// - Nombre del puerto a abrir ("COM1", "COM2", "COM3", ...).
// - Velocidad (1200, 1400, 4800, 9600, 19200, 38400, 57600, 115200).
// - Número de bits en cada byte enviado o recibido (4, 5, 6, 7, 8).
// - Paridad (0=sin paridad, 1=impar, 2=par, 3=marca, 4=espacio).
// - Bits de stop (0=1 bit, 1=1.5 bits, 2=2 bits)
	PuertoCOM = AbrirPuerto("COM1", 9600, 8, 0, 0); //Abrimos el puerto COM1 (en la sala siempre abrimos el COM1)
	if (PuertoCOM == NULL) {
		printf("Error al abrir el puerto\n");
		getch();
		return (1);
	} else
		printf("Puerto abierto correctamente\n");


// Lectura y escritura simultánea de caracteres:
	while (car != 27) {
		car = RecibirCaracter(PuertoCOM);
		if (car)
			printf("%c", car);       //Recepción
		if (kbhit()) {
			car = getch();
			if (car != 27) {
				printf("%c", car);   //Envío
				EnviarCaracter(PuertoCOM, car);
			}
		}
	}


// Para cerrar el puerto:
	CerrarPuerto(PuertoCOM);

	return 0;
}
