#include "Provincia.h"
#include <iostream>
#include <string.h>

Provincia::Provincia(int id, const char* nombre) {
	std::cout << "Constructor Provincia" << std::endl;
	this->id = id;
	this->nombre = new char[strlen(nombre) + 1];
	strcpy(this->nombre, nombre);
}

Provincia::~Provincia() {
	std::cout << "Destructor Persona" << std::endl;
	delete[] nombre;
}

const char* Provincia::getNombre(){
	return this->nombre;
}

int Provincia::getId(){
	return this->id;
}

void Provincia::setNombre(char* nombre){
	this->nombre = nombre;
};

void Provincia::setId(int id){
	this->id = id;
};

void Provincia::imprimirProvincia(){
	std::cout << "Nombre: " << this->getNombre() << " Id: " << this->getId() << std::endl;
}
