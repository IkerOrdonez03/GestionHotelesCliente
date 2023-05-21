#ifndef CLASES_PERSONA_H_
#define CLASES_PERSONA_H_

class Persona
{
	char *nombre;
	int dni;

public:
	Persona(const char* nombre, int dni);
	Persona(const Persona &p);
	virtual ~Persona();

	const char* getNombre();
	int getDni();
};

#endif
