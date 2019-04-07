
#ifndef PRACTICAPUERTOCOM_ESCRITORPUERTOCOM_P_ME_H
#define PRACTICAPUERTOCOM_ESCRITORPUERTOCOM_P_ME_H

#include <vector>
#include <algorithm>
#include "ManejadorPuertoCOM.h"
#include "TramaDatos.h"

/**
 * Clase que implementa el envío de fichero pensando en su uso en el protocolo maestro-esclavo.
 * Cada trama enviada debe ser confirmada
 *
 * @author Juan Pablo García Plaza Pérez @ 2ºGIIIS/GrupoA
 * @author José Ángel Concha Carrasco @ 2ºGIIIS/GrupoA
 */
class EscritorPuertoCOM_P_ME {

private:
	/**
	 * Manejador del puerto COM
	 */
	ManejadorPuertoCOM *mPuertoCOM;

	/**
	 * Buffer de tramas enviadas
 	 */
	vector<Trama *> bufferTramas;

private:
	/**
	 * Comprueba si el manejador del puerto COM está inicializado
	 */
	bool manPrtoCOMAbierto();

	/**
	 * Método modificador del atributo 'bufferTramas'
	 *
	 * @param bufferTramas Nuevo buffer de tramas
	 */
	void setBufferTramas(vector<Trama *> bufferTramas);

public:
	/**
	 * @param mPuertoCOM Manejador del puerto COM
	 */
	EscritorPuertoCOM_P_ME(ManejadorPuertoCOM *mPuertoCOM);

	/**
	 * Envía una trama de control por el puerto COM
	 *
	 * @param tramaDatos Trama de control a enviar
	 */
	void enviarTramaControl(Trama tramaControl);

	/**
	 * Envía una trama de datos por el puerto COM
	 *
	 * @param tramaDatos Trama de datos a enviar
	 */
	void enviarTramaDatos(TramaDatos tramaDatos);

	/**
	* @return Buffer de tramas enviadas
	*/
	vector<Trama *> getBufferTramas();

	/**
	 * Libera la memoria asociada a las tramas del buffer. Debe ser llamado antes de volver a asignar el buffer para
	 * evitar fugas de memoria
	 */
	void liberarBufferTramas();
};


#endif //PRACTICAPUERTOCOM_ESCRITORPUERTOCOM_P_ME_H
