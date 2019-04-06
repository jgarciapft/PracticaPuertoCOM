
#ifndef PRACTICAPUERTOCOM_PROTOCOLOESTANDAR_H
#define PRACTICAPUERTOCOM_PROTOCOLOESTANDAR_H

#include "Protocolo.h"

/**
 * Clase que implementa el protocolo est�ndar de la aplicaci�n. Es el implementado hasta la Sesion_4
 *
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
class ProtocoloEstandar : public Protocolo {

private:
	/**
	 * Establece la primera fase de comunicaci�n del protocolo y pasa a la fase de transimisi�n
	 *
	 * @return Si se desea terminar la aplicaci�n
	 */
	bool establecimiento() override;

	/**
	 * Fase de transimisi�n de datos y pasa a la fase de liberaci�n
	 *
	 * @return Si se desea terminar la aplicaci�n
	 */
	bool transmision() override;

	/**
	 * Instrucciones finales antes de cerrar el protocolo
	 *
	 * @return Si se desea terminar la aplicaci�n
	 */
	bool liberacion() override;

public:
	/**
	 * @param lectorPuertoCom Lector que maneje la lectura de datos
	 * @param escritorPuertoCom Escritor que maneje la escritura de datos
	 */
	ProtocoloEstandar(LectorPuertoCOM *lectorPuertoCom, EscritorPuertoCOM *escritorPuertoCom);

	/**
	 * Inicia el protocolo y lo maneja de inicio a fin
	 *
	 * @return Si se desea terminar la aplicaci�n
	 */
	bool iniciar() override;
};


#endif //PRACTICAPUERTOCOM_PROTOCOLOESTANDAR_H
