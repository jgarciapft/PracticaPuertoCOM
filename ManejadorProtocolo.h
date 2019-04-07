
#ifndef PRACTICAPUERTOCOM_MANEJADORPROTOCOLO_H
#define PRACTICAPUERTOCOM_MANEJADORPROTOCOLO_H

#include "Protocolo.h"
#include "ProtocoloEstandar.h"

/**
 * Manejador del flujo de programa relacionado con el cambio de protocolos a elecci�n
 *
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
class ManejadorProtocolo {

private:
	/**
	 * Instancia del protocolo est�ndar
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
	 * M�todo modificador del atributo 'protocoloActual'
	 *
	 * @param protocoloActual Nuevo protocolo en uso
	 */
	void setProtocoloActual(Protocolo *protocoloActual);

public:
	/**
	 * @param lectorPuertoCOM Lector que maneje la lectura de datos
	 * @param EscritorPuertoCOM Escritor que maneje la escritura de datos
	 */
	ManejadorProtocolo(LectorPuertoCOM *lectorPuertoCOM, EscritorPuertoCOM *EscritorPuertoCOM);

	~ManejadorProtocolo();

	/**
	 * Maneja el cambio de protocolos y el resto del flujo de la aplicaci�n
	 */
	void ejecutar();
};


#endif //PRACTICAPUERTOCOM_MANEJADORPROTOCOLO_H
