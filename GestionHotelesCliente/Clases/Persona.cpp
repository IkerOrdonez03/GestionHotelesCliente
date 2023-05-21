#include "Persona.h"
#include <string.h>

#include <iostream>
using namespace std;

Persona::Persona(const char *nombre, int id)
{
	cout << "Constructor Persona" << endl;
	this->nombre = new char[strlen(nombre) + 1];
	strcpy(this->nombre, nombre);
	this->id = id;
}

Persona::Persona(const Persona& p)
{
	cout << "Constructor Copia Persona" << endl;
	this->nombre = new char[strlen(p.nombre) + 1];
	strcpy(this->nombre, p.nombre);
	this->id = p.id;
}

Persona::~Persona()
{
	cout << "Destructor Persona" << endl;
	delete[] nombre;
}

const char* Persona::getNombre()
{
	return this->nombre;
}

int Persona::getId()
{
	return this->id;
}
