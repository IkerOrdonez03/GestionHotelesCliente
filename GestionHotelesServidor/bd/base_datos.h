
#ifndef BASE_DATOS_H_
#define BASE_DATOS_H_

#include <iostream>
#include <stdio.h>
#include "sqlite3.h"
#include "../Clases/Provincias.h"
#include "../Clases/Hoteles.h"
#include "../logger/log.h"
#include "../reserva/reserva.h"


char* parseInt(char *resultado, int n);
int validadAdmin(char* usuario, char* clave, sqlite3* db);
int contarProvincias(sqlite3* db);
int contarHoteles(sqlite3 *db);
int initHoteles(Hoteles* hoteles, sqlite3* db, Provincias* provincias);
int initProvinvias(Provincias* provincias, sqlite3* db);
int insertarReserva(Reserva *reserva, sqlite3* db);
int validaCliente(char* usuario, char* clave, sqlite3* db);
int insertarCliente(const std::string& dni, const std::string& nombre, const std::string& direccion, const std::string& telefono, const std::string& usuario, const std::string& clave, sqlite3* db);
int eliminarReserva(const std::string& id, sqlite3* db);

#endif /* BASE_DATOS_H_ */
