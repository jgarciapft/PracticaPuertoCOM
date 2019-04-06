
#ifndef PRACTICAPUERTOCOM_PROTOCOLO_H
#define PRACTICAPUERTOCOM_PROTOCOLO_H


#include "LectorPuertoCOM.h"

class Protocolo {

private:
	/**
	 * Lector que maneje la lectura de datos
	 */
	LectorPuertoCOM *lectorPuertoCom;
	/**
	 * Escritor que maneje la escritura de datos
	 */
	EscritorPuertoCOM *escritorPuertoCom;

private:
	/**
	 * Establece la primera fase de comunicación del protocolo
	 */
	virtual void establecimiento() = 0;

	/**
	 * Fase de transimisión de datos
	 */
	virtual void transmision() = 0;

	/**
	 * Instrucciones finales antes de cerrar el protocolo
	 */
	virtual void liberacion() = 0;

public:
	/**
	 * @param lectorPuertoCom Lector que maneje la lectura de datos
	 * @param escritorPuertoCom Escritor que maneje la escritura de datos
	 */
	Protocolo(LectorPuertoCOM *lectorPuertoCom, EscritorPuertoCOM *escritorPuertoCom);

	/**
	 * Inicia el protocolo y lo maneja de inicio a fin
	 */
	virtual void iniciar() = 0;

protected:
	LectorPuertoCOM *getLectorPuertoCOM();

	EscritorPuertoCOM *getEscritorPuertoCOM();
};


#endif //PRACTICAPUERTOCOM_PROTOCOLO_H
