#ifndef PROVINCIA_H_
#define PROVINCIA_H_

typedef struct {
	int id;
	char name[20];
} Provincia;

typedef struct {
	Provincia *provincias;
	int numProvincias;
} Provincias;

void imprimirProvincia(Provincia*);

#endif /* PROVINCIA_H_ */
