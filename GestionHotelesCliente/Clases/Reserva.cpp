#include "Reserva.h"
#include <string.h>

#include <iostream>
using namespace std;

Reserva::Reserva(int id, int dia_ini, int mes_ini, int ano_ini, int dia_fin, int mes_fin, int ano_fin, int id_hab, int dni_cliente) {
	cout << "Constructor Reserva" << endl;
	this->id = id;
	this->dia_ini = dia_ini;
	this->mes_ini = mes_ini;
	this->ano_ini = ano_ini;
	this->dia_fin = dia_fin;
	this->mes_fin = mes_fin;
	this->ano_fin = ano_fin;
	this->id_hab = id_hab;
	this->dni_cliente = dni_cliente;
}

Reserva::Reserva(const Reserva &r) {
	cout << "Constructor Copia Reserva" << endl;
	this->id = r.id;
	this->dia_ini = r.dia_ini;
	this->mes_ini = r.mes_ini;
	this->ano_ini = r.ano_ini;
	this->dia_fin = r.dia_fin;
	this->mes_fin = r.mes_fin;
	this->ano_fin = r.ano_fin;
	this->id_hab = r.id_hab;
	this->dni_cliente = r.dni_cliente;

}

Reserva::~Reserva() {
	cout << "Destructor Reserva" << endl;
}

int Reserva::getId()
{
	return this->id;
}

int Reserva::getDia_Ini()
{
	return this->dia_ini;
}

int Reserva::getMes_Ini()
{
	return this->mes_ini;
}

int Reserva::getAno_Ini()
{
	return this->ano_ini;
}

int Reserva::getDia_Fin(){
	return this->dia_fin;
}

int Reserva::getMes_Fin(){
	return this->mes_fin;
}

int Reserva::getAno_Fin(){
	return this->ano_fin;
}

int Reserva::getIdHab(){
	return this->id_hab;
}

int Reserva::getDniCliente()
{
	return this->dni_cliente;
}
