
#ifndef PRACTICAPUERTOCOM_PROTOCOLO_H
#define PRACTICAPUERTOCOM_PROTOCOLO_H

#include "LectorPuertoCOM.h"
#include "EscritorPuertoCOM.h"

/**
 * Clase base que modela el comportamiento de un protocolo. Sirve de interfaz sobre la quye construir un protocolo
 * de aplicación específico. Establece el funcionamiento del protocolo en 3 fases: establecimiento, transmisión y
 * liberación
 *
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
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
	 * Establece la primera fase de comunicación del protocolo y pasa a la fase de transimisión
	 *
	 * @return Si se desea terminar la aplicación
	 */
	virtual bool establecimiento() = 0;

	/**
	 * Fase de transimisión de datos y pasa a la fase de liberación
	 *
	 * @return Si se desea terminar la aplicación
	 */
	virtual bool transmision() = 0;

	/**
	 * Instrucciones finales antes de cerrar el protocolo
	 *
	 * @return Si se desea terminar la aplicación
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
	 * @return Si se desea terminar la aplicación
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
