
#ifndef PRACTICAPUERTOCOM_PROTOCOLOESTANDAR_H
#define PRACTICAPUERTOCOM_PROTOCOLOESTANDAR_H

#include "Protocolo.h"

/**
 * Clase que implementa el protocolo estándar de la aplicación. Es el implementado hasta la Sesion_4
 *
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
 */
class ProtocoloEstandar : public Protocolo {

private:
	/**
	 * Establece la primera fase de comunicación del protocolo y pasa a la fase de transimisión
	 *
	 * @return Si se desea terminar la aplicación
	 */
	bool establecimiento() override;

	/**
	 * Fase de transimisión de datos y pasa a la fase de liberación
	 *
	 * @return Si se desea terminar la aplicación
	 */
	bool transmision() override;

	/**
	 * Instrucciones finales antes de cerrar el protocolo
	 *
	 * @return Si se desea terminar la aplicación
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
	 * @return Si se desea terminar la aplicación
	 */
	bool iniciar() override;
};


#endif //PRACTICAPUERTOCOM_PROTOCOLOESTANDAR_H
