
#ifndef BASE_DATOS_H_
#define BASE_DATOS_H_

#include <iostream>
#include <stdio.h>
#include "sqlite3.h"
#include "../Clases/Provincias.h"
#include "../Clases/Hoteles.h"
#include "../logger/log.h"
#include "../reserva/reserva.h"


// Primera entrega
int validadAdmin(char*, char*, sqlite3*); // 0 es valido(el resto invalido)
int validaCliente(char* usuario, char* clave, sqlite3* db);
int contarProvincias(sqlite3*);
int initProvincias (Provincias*, sqlite3*);
int contarHoteles(sqlite3*);
int initHoteles (Hoteles*, sqlite3*, Provincias*);
int insertarHotel (Hotel *, sqlite3*);
int insertarReserva(Reserva *, sqlite3*);
int eliminarHotel (Hotel*, sqlite3*);
int eliminarReserva(const std::string&, sqlite3*);
int validaCliente(char*, char*, sqlite3*); // 0 es valido(el resto invalido)
int insertarCliente(const std::string& dni, const std::string& nombre, const std::string& direccion, const std::string& telefono, const std::string& usuario, const std::string& clave, sqlite3* db);

#endif /* BASE_DATOS_H_ */
