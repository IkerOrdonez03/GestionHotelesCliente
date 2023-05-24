#include "Provincias.h"


Provincia Provincias::getProvinciaPorId(int id){
	for(int n; n < this->numProvincias; ++n){
		if(this->provincias[n].getId() == id){
			return this->provincias[n];
		}
	}
	return this->provincias[0];
}
