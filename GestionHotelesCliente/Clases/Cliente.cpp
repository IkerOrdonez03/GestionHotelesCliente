#include "Cliente.h"

#include <iostream>
#include <string.h>
using namespace std;

Cliente::Cliente(const char* nombre, int dni, const char *direccion, int telefono, const char *usuario, const char *clave):Persona(nombre, dni) {
	cout << "Constructor Cliente" << endl;
	this->direccion = new char[strlen(direccion) + 1];
	strcpy(this->direccion, direccion);
	this->telefono = telefono;
	this->usuario = new char[strlen(usuario) + 1];
	strcpy(this->usuario, usuario);
	this->clave = new char[strlen(clave) + 1];
	strcpy(this->clave, clave);
}

Cliente::Cliente(const Cliente &c):Persona(c) {
	cout << "Constructor Copia Cliente" << endl;
	this->direccion = new char[strlen(c.direccion) + 1];
	strcpy(this->direccion, c.direccion);
	this->telefono = c.telefono;
	this->usuario = new char[strlen(c.usuario) + 1];
	strcpy(this->usuario, c.usuario);
	this->clave = new char[strlen(c.clave) + 1];
	strcpy(this->clave, c.clave);

}

Cliente::~Cliente() {
	cout << "Destructor Cliene" << endl;
	delete[] direccion;
	delete[] usuario;
	delete[] clave;
}

const char* Cliente::getDireccion()
{
	return this->direccion;
}

int Cliente::getTelefono()
{
	return this->telefono;
}

const char* Cliente::getUsuario()
{
	return this->usuario;
}

const char* Cliente::getClave()
{
	return this->clave;
}
