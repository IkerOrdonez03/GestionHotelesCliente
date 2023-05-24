#include <iostream>
#include <string.h>
#include "Hotel.h"


Hotel::Hotel() {
	id = 0;
	nombre = 0;
	estrellas = 0;
	provincia = 0;
}

Hotel::Hotel(int id, const char* nombre, int estrellas, Provincia* provincia) {
	this->id = id;
	this->nombre = new char[strlen(nombre + 1)];
	strcpy(this->nombre, nombre);
	this->estrellas = estrellas;
	this->provincia = provincia;
}

Hotel::Hotel(const Hotel &h) {
	this->id = h.id;
	this->nombre = new char[strlen(h.nombre + 1)];
	strcpy(this->nombre, h.nombre);
	this->estrellas = estrellas;
	this->provincia = h.provincia;
}

Hotel::~Hotel() {
	delete[] nombre;
}

int Hotel::getId() {
	return id;
}

void Hotel::setId(int id) {
	this->id = id;
}

char* Hotel::getNombre() {
	return nombre;
}

void Hotel::setNombre(const char *nombre) {
	delete[] nombre;
	this->nombre = new char[strlen(nombre + 1)];
	strcpy(this->nombre, nombre);
}

int Hotel::getEstrellas() {
	return estrellas;
}

void Hotel::setEstrellas(int estrellas) {
	this->estrellas = estrellas;
}

Provincia Hotel::getProvincia() {
	return *provincia;
}

void Hotel::setProvincia(Provincia *provincia) {
	this->provincia = provincia;
}
