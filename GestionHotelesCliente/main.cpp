#include "Clases\Persona.h"

#include <iostream>
using namespace std;

void printPersona(Persona p)
{
	cout << "Nombre: " << p.getNombre() << endl;
	cout << "DNI: " << p.getDni() << endl;
}

int main()
{
	Persona *p1 = new Persona("Juanito", 15);
	printPersona(*p1);
	delete p1;
	return 0;
}
