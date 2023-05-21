/*
 * Habitacion.cpp
 *
 *  Created on: 21 may 2023
 *      Author: benat
 */

#include "Habitacion.h"

Habitacion::Habitacion() {
	id = 0;
	numero = 0;
	tipo = 0;
	capacidad = 0;
	precio = 0;
	// hotel = 0;
}

Habitacion::Habitacion(int id, int numero, const char* tipo, int capacidad, int precio, Hotel hotel) {
	this->id = id;
	this->numero = numero;
	this->tipo = new char[strlen(tipo + 1)];
	strcpy(this->tipo, tipo);
	this->capacidad = capacidad;
	this->precio = precio;
	this->hotel = Hotel(hotel);
}

Habitacion::Habitacion(const Habitacion &h) {
	this->id = h.id;
	this->numero = h.numero;
	this->tipo = new char[strlen(h.tipo + 1)];
	strcpy(this->tipo, h.tipo);
	this->capacidad = h.capacidad;
	this->precio = h.precio;
	this->hotel = Hotel(h.hotel);
}

Habitacion::~Habitacion() {
	delete[] tipo;
}
