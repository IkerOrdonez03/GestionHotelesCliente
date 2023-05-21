#ifndef CLASES_PERSONA_H_
#define CLASES_PERSONA_H_

class Persona
{
	char *nombre;
	int id;

public:
	Persona(const char* nombre, int id);
	Persona(const Persona &p);
	virtual ~Persona();

	const char* getNombre();
	int getId();
};

#endif
