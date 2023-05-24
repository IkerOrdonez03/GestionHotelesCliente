#ifndef CLASES_PROVINCIA_H_
#define CLASES_PROVINCIA_H_

class Provincia {
public:
	Provincia(int id, const char* nombre);
	virtual ~Provincia();
	const char* getNombre();
	int getId();
	void imprimirProvincia();

private:
	int id;
	char* nombre;
};

#endif /* CLASES_PROVINCIA_H_ */
