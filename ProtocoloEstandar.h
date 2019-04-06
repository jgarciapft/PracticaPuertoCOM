
#ifndef PRACTICAPUERTOCOM_PROTOCOLOESTANDAR_H
#define PRACTICAPUERTOCOM_PROTOCOLOESTANDAR_H

#include "Protocolo.h"

class ProtocoloEstandar : public Protocolo{

private:
	void establecimiento() override;

	void transmision() override;

	bool liberacion(bool finAplicacion) override;

public:
	ProtocoloEstandar(LectorPuertoCOM *lectorPuertoCom, EscritorPuertoCOM *escritorPuertoCom);

	void iniciar() override;
};


#endif //PRACTICAPUERTOCOM_PROTOCOLOESTANDAR_H
