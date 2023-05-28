#ifndef CLASES_PROVINCIAS_H_
#define CLASES_PROVINCIAS_H_
#include "Provincia.h"

class Provincias {
public:
	Provincia *provincias;
	int numProvincias;
	Provincia getProvinciaPorId(int);
};

#endif
