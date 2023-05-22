#ifndef HOTEL_H_
#define HOTEL_H_

#include "../provincia/provincia.h"

typedef struct {
	int id;
	char name[50];
	int estrellas;
	Provincia* provincia;
} Hotel;

typedef struct {
	Hotel *hoteles;
	int numHoteles;
} Hoteles;

void imprimirHotel(Hotel*);

#endif /* HOTEL_H_ */
