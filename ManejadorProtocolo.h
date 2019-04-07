
#ifndef PRACTICAPUERTOCOM_MANEJADORPROTOCOLO_H
#define PRACTICAPUERTOCOM_MANEJADORPROTOCOLO_H

#include "Protocolo.h"
#include "ProtocoloEstandar.h"

/**
 * Manejador del flujo de programa relacionado con el cambio de protocolos a elección
 *
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
 */
class ManejadorProtocolo {

private:
	/**
	 * Instancia del protocolo estándar
	 */
	const Protocolo *protocoloEstandar;
	/**
	 * Instancia del protocolo Maestro-Esclavo
	 */
	const Protocolo *protocoloMaestroEsclavo;
	/**
	 * Protocolo actual en uso
	 */
	Protocolo *protocoloActual;

private:
	/**
	 * @return Protocolo actual en uso
	 */
	Protocolo *getProtocoloActual();

	/**
	 * Alterna entre protocolos
	 */
	void cambiarProtocoloActual();

public:
	ManejadorProtocolo();

	~ManejadorProtocolo();

	/**
	 * Maneja el cambio de protocolos y el resto del flujo de la aplicación
	 */
	void ejecutar();
};


#endif //PRACTICAPUERTOCOM_MANEJADORPROTOCOLO_H
