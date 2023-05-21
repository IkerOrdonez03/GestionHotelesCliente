/*
 * Provincia.cpp
 *
 *  Created on: May 21, 2023
 *      Author: unaialonso
 */

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

void Provincia::imprimirProvincia(Provincia p){
	std::cout << "Nombre: " << p.getNombre() << " Id: " << p.getNombre() << std::endl;
}

