/*
 * Hotel.h
 *
 *  Created on: 21 may 2023
 *      Author: benat
 */

#ifndef CLASES_HOTEL_H_
#define CLASES_HOTEL_H_

#include <string.h>
#include "Provincia.h"

class Hotel {
private:
	int id;
	char* nombre;
	int estrellas;
	Provincia* provincia; // es un puntero porque la provincia no cambia sus atributos
public:
	Hotel();
	Hotel(int, const char*, int, Provincia*);
	Hotel(const Hotel &other);
	virtual ~Hotel();

	int getId();
	void setId(int id);
	char* getNombre();
	void setNombre(const char* nombre);
	int getEstrellas();
	void setEstrellas(int estrellas);
	Provincia getProvincia();
	void setProvincia(Provincia* provincia);
};

#endif /* CLASES_HOTEL_H_ */
