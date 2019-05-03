
#ifndef PRACTICAPUERTOCOM_CONSTANTES_H
#define PRACTICAPUERTOCOM_CONSTANTES_H

/**
 * Almac�n de constantes p�blicas
 *
 * @author Juan Pablo Garc�a Plaza P�rez @ 2�GIIIS/GrupoA
 * @author Jos� �ngel Concha Carrasco @ 2�GIIIS/GrupoA
 */
class CONSTANTES {

public:
	/**
	 * Caracter indicador del inicio del env�o de un fichero
	 */
	static const char CHAR_INICIO_FICHERO = '#';
	/**
	 * Caracter indicador del fin del env�o de un fichero
	 */
	static const char CHAR_FIN_FICHERO = '@';
	/**
	* Colecci�n de c�digos ASCII de tipos de trama
	*/
	enum COD_CONTROL_TRAMA {
		STX = 2, ENQ = 5, EOT = 4, ACK = 6, NACK = 21
	};

	/**
	 * Tipo enumerado de c�digos ASCII �tiles para el programa
	 */
	enum COD_ASCII {
		ESCAPE = 27,
		SINCRONISMO = 22,
		TECLA_FUNCION = '\0',
		TECLA_F1 = 59,
		TECLA_F2 = 60,
		TECLA_F3 = 61,
		TECLA_F4 = 62,
		TECLA_F5 = 63,
		TECLA_RETROCESO = '\b',
		TECLA_RETORNO = 13,
		CRLN = '\n',
		DELIM_CAD = '\0'
	};

	/**
	 * Enumerado con los tipos de protocolos implementados
	 */
	enum PROTOCOLOS {
		ESTANDAR, MAESTROESCLAVO
	};

	/**
	 * Tipo enumerado para el campo de direcci�n de las tramas en el protocolo maestro-esclavo
	 */
	enum OP_PROTOC_ME {
		SELECCION = 'R', SONDEO = 'T'
	};

};


#endif //PRACTICAPUERTOCOM_CONSTANTES_H
