/*
 * Habitacion.h
 *
 *  Created on: 21 may 2023
 *      Author: benat
 */

#ifndef CLASES_HABITACION_H_
#define CLASES_HABITACION_H_

#include "Hotel.h"
#include <string.h>
#include <stdio.h>


class Habitacion {
private:
	int id;
	int numero;
	char* tipo;
	int capacidad;
	int precio;
	Hotel hotel;

public:
	Habitacion();
	Habitacion(int, int, const char*, int, int, Hotel);
	Habitacion(const Habitacion &other);
	virtual ~Habitacion();


};

#endif /* CLASES_HABITACION_H_ */
