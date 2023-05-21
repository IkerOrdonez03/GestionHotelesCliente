#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "Persona.h"

class Cliente: public Persona {
	char *direccion;
	int telefono;
	char *usuario;
	char *clave;

public:
	Cliente(const char* nombre, int dni, const char *direccion, int telefono, const char *usuario, const char *clave);
	Cliente(const Cliente &c);
	virtual ~Cliente();

	const char* getDireccion();
	int getTelefono();
	const char* getUsuario();
	const char* getClave();
};

#endif
