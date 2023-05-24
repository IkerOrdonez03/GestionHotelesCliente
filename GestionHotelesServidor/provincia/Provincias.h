#ifndef PROVINCIA_PROVINCIAS_H_
#define PROVINCIA_PROVINCIAS_H_
#include "Provincia.h"

class Provincias {
public:
	Provincia *provincias;
	int numProvincias;
	Provincia getProvinciaPorId(int);
};

#endif /* PROVINCIA_PROVINCIAS_H_ */
