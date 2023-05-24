#ifndef CLASES_PROVINCIA_H_
#define CLASES_PROVINCIA_H_

class Provincia {
private:
	int id;
	char* nombre;
public:
	Provincia(int id, const char* nombre);
	virtual ~Provincia();
	const char* getNombre();
	int getId();
	void setNombre(char*);
	void setId(int);
	void imprimirProvincia();

};

#endif /* CLASES_PROVINCIA_H_ */
