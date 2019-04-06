
#ifndef PRACTICAPUERTOCOM_PROTOCOLO_H
#define PRACTICAPUERTOCOM_PROTOCOLO_H

#include "LectorPuertoCOM.h"
#include "EscritorPuertoCOM.h"

/**
 * Clase base que modela el comportamiento de un protocolo. Sirve de interfaz sobre la quye construir un protocolo
 * de aplicaci�n espec�fico. Establece el funcionamiento del protocolo en 3 fases: establecimiento, transmisi�n y
 * liberaci�n
 *
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
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
	 * Establece la primera fase de comunicaci�n del protocolo y pasa a la fase de transimisi�n
	 *
	 * @return Si se desea terminar la aplicaci�n
	 */
	virtual bool establecimiento() = 0;

	/**
	 * Fase de transimisi�n de datos y pasa a la fase de liberaci�n
	 *
	 * @return Si se desea terminar la aplicaci�n
	 */
	virtual bool transmision() = 0;

	/**
	 * Instrucciones finales antes de cerrar el protocolo
	 *
	 * @return Si se desea terminar la aplicaci�n
	 */
	virtual bool liberacion() = 0;

public:
	/**
	 * @param lectorPuertoCom Lector que maneje la lectura de datos
	 * @param escritorPuertoCom Escritor que maneje la escritura de datos
	 */
	Protocolo(LectorPuertoCOM *lectorPuertoCom, EscritorPuertoCOM *escritorPuertoCom);

	/**
	 * Inicia el protocolo y lo maneja de inicio a fin
	 *
	 * @return Si se desea terminar la aplicaci�n
	 */
	virtual bool iniciar() = 0;

	virtual ~Protocolo();

protected:
	/**
	 * @return Lector que maneje la lectura de datos
	 */
	LectorPuertoCOM *getLectorPuertoCOM();

	/**
	 * @return Escritor que maneje la escritura de datos
	 */
	EscritorPuertoCOM *getEscritorPuertoCOM();
};


#endif //PRACTICAPUERTOCOM_PROTOCOLO_H
