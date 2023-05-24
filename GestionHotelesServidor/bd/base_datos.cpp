#include "base_datos.h"
#include "../reserva/reserva.h"
#include "../Clases/Hotel.h"
#include "../Clases/Provincia.h"
#include "../Clases/Provincias.h"
#include "../Clases/Hoteles.h"
#include <iostream>
#include <string>
#include <cstring>
#include "sqlite3.h"

std::string mensaje;

char* parseInt(char *resultado, int n){
	sprintf(resultado, "%d", n);
	return resultado;
}

int validadAdmin(char* usuario, char* clave, sqlite3* db) {
    char c[30];

    sqlite3_stmt* stmt;
    const char* sql = "SELECT CLAVE_ADMIN FROM ADMINISTRADOR WHERE USUARIO_ADMIN = ?";
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if (result != SQLITE_OK) {
        mensaje = "Error preparing statement (SELECT)" + std::string(sqlite3_errmsg(db));
        std::cout << mensaje << std::endl;
    }
    else {
        mensaje = "SQL query prepared (SELECT)";
        std::cout << mensaje << std::endl;
    }
    result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        strcpy(c, (char*)sqlite3_column_text(stmt, 0));
    }
    result = sqlite3_finalize(stmt);
    return strcmp(c, clave);
}

int contarProvincias(sqlite3* db) {
    int contador;
    sqlite3_stmt* stmt;
    const char* sql = "SELECT COUNT(ID_PROV) FROM PROVINCIA";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if (result != SQLITE_OK) {
        mensaje = "Error preparing statement (SELECT)" + std::string(sqlite3_errmsg(db));
        std::cout << mensaje << std::endl;
    }
    else {
        mensaje = "SQL query prepared (SELECT)";
        std::cout << mensaje << std::endl;
    }

    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        contador = sqlite3_column_int(stmt, 0);
    }
    result = sqlite3_finalize(stmt);

    return contador;
}


int contarHoteles(sqlite3 *db) {
	int contador;
	sqlite3_stmt *stmt;
		char sql[] = "SELECT COUNT(ID_HOTEL) FROM HOTEL";

		int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
		if (result != SQLITE_OK) {
			 mensaje = "Error preparing statement (SELECT)" + std::string(sqlite3_errmsg(db));
			std::cout << mensaje << std::endl;
		}
		else {
			mensaje = "SQL query prepared (SELECT)";
			std::cout << mensaje << std::endl;
		}
		result = sqlite3_step(stmt) ;
			if (result == SQLITE_ROW) {
				contador = sqlite3_column_int(stmt, 0);
			}
		result = sqlite3_finalize(stmt);

		return contador;
}

int initHoteles(Hoteles* hoteles, sqlite3* db, Provincias* provincias) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT ID_HOTEL, NOM_HOTEL, NUM_ESTTRELLAS, ID_PROV FROM HOTEL";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if (result != SQLITE_OK) {
        mensaje = "Error preparing statement (SELECT)" + std::string(sqlite3_errmsg(db));
        std::cout << mensaje << std::endl;
    }
    else {
        mensaje = "SQL query prepared (SELECT)";
        std::cout << mensaje << std::endl;
    }
    hoteles->numHoteles = contarHoteles(db);
    memset(hoteles->hoteles, 0, hoteles->numHoteles * sizeof(Hotel));
    for (int i = 0; i < contarHoteles(db); ++i) {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            for (int n = 0; n < contarProvincias(db); ++n) {
            	hoteles->hoteles[i].setId(sqlite3_column_int(stmt, 0));
            	hoteles->hoteles[i].setNombre((char*)sqlite3_column_text(stmt, 1));
            	hoteles->hoteles[i].setEstrellas(sqlite3_column_int(stmt, 2));
            	Provincia prov = provincias->getProvinciaPorId(sqlite3_column_int(stmt, 3));
            	hoteles->hoteles[i].setProvincia(&prov);
            }
        }
    }

    result = sqlite3_finalize(stmt);

    return result;
}

int initProvinvias(Provincias* provincias, sqlite3* db) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT ID_PROV, NOM_PROV FROM PROVINCIA";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if (result != SQLITE_OK) {
        mensaje = "Error preparing statement (SELECT)" + std::string(sqlite3_errmsg(db));
        std::cout << mensaje << std::endl;
    }
    else {
        mensaje = "SQL query prepared (SELECT)";
        std::cout << mensaje << std::endl;
    }
    provincias->numProvincias = contarProvincias(db);
    memset(provincias->provincias, 0, provincias->numProvincias * sizeof(Provincia));
    for (int i = 0; i < provincias->numProvincias; ++i) {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
        	provincias->provincias[i].setId(sqlite3_column_int(stmt, 0));
        	provincias->provincias[i].setNombre((char*)sqlite3_column_text(stmt, 1));
        }
    }

    result = sqlite3_finalize(stmt);

    return result;
}


int insertarReserva(Reserva *reserva, sqlite3* db){
	sqlite3_stmt* stmt;
	const char* sql = "INSERT INTO RESERVA (ID_RES, DIA_INI, MES_INI, ANO_INI, DIA_FIN, MES_FIN, ANO_FIN, ID_HAB, DNI) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ? )";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
	if (result != SQLITE_OK) {
		std::cout << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
		return result;
	}

	char idC[10];
	parseInt(idC, reserva->getId());
	result = sqlite3_bind_text(stmt, 1, idC, -1, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		std::cerr << "Error al asociar el valor a la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
	}

	char diaIC[10];
	parseInt(diaIC, reserva->getDia_Ini());
	result = sqlite3_bind_text(stmt, 2, diaIC, -1, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		std::cerr << "Error al asociar el valor a la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
	}

	char mesIC[10];
	parseInt(mesIC, reserva->getMes_Ini());
	result = sqlite3_bind_text(stmt, 3, mesIC, -1, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		std::cerr << "Error al asociar el valor a la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
	}

	char anoIC[10];
	parseInt(anoIC, reserva->getAno_Ini());
	result = sqlite3_bind_text(stmt, 4, anoIC, -1, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		std::cerr << "Error al asociar el valor a la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
	}

	char diaFC[10];
	parseInt(diaFC, reserva->getDia_Fin());
	result = sqlite3_bind_text(stmt, 5, diaFC, -1, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		std::cerr << "Error al asociar el valor a la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
	}

	char mesFC[10];
	parseInt(mesFC, reserva->getMes_Fin());
	result = sqlite3_bind_text(stmt, 6, mesFC, -1, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		std::cerr << "Error al asociar el valor a la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
	}

	char anoFC[10];
	parseInt(anoFC, reserva->getAno_Fin());
	result = sqlite3_bind_text(stmt, 7, anoFC, -1, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		std::cerr << "Error al asociar el valor a la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
	}


	char idH[10];
	parseInt(idH, reserva->getId());
	result = sqlite3_bind_text(stmt, 8, idH, -1, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		std::cerr << "Error al asociar el valor a la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
	}

	char dniC[10];
	parseInt(dniC, reserva->getDniCliente());
	result = sqlite3_bind_text(stmt, 9, dniC, -1, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		std::cerr << "Error al asociar el valor a la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		std::cout << "Error inserting client: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_finalize(stmt);
		return result;
	}

	sqlite3_finalize(stmt);
	return SQLITE_OK;
}

int validaCliente(char* usuario, char* clave, sqlite3* db) {
    char c[30];

    sqlite3_stmt* stmt;
    const char* sql = "SELECT CLAVE_CLTE FROM CLIENTE WHERE USUARIO_CLTE = ?";
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if (result != SQLITE_OK) {
        mensaje = "Error preparing statement (SELECT)" + std::string(sqlite3_errmsg(db));
        std::cout << mensaje << std::endl;
    }
    else {
        mensaje = "SQL query prepared (SELECT)";
        std::cout << mensaje << std::endl;
    }
    result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        strcpy(c, (char*)sqlite3_column_text(stmt, 0));
    }
    result = sqlite3_finalize(stmt);
    return strcmp(c, clave);
}

int insertarCliente(const std::string& dni, const std::string& nombre, const std::string& direccion, const std::string& telefono, const std::string& usuario, const std::string& clave, sqlite3* db) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO CLIENTE (DNI, NOM_CLTE, DIR_CLTE, TF_CLTE, USUARIO_CLTE, CLAVE_CLTE) VALUES (?, ?, ?, ?, ?, ? )";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    if (result != SQLITE_OK) {
        std::cout << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return result;
    }

    result = sqlite3_bind_text(stmt, 1, dni.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
		std::cerr << "Error al asociar el valor a la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
	}
    result = sqlite3_bind_text(stmt, 2, nombre.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        std::cerr << "Error al asociar el valor a la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
    }
    result = sqlite3_bind_text(stmt, 3, direccion.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        std::cerr << "Error al asociar el valor a la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
    }
    result = sqlite3_bind_text(stmt, 4, telefono.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        std::cerr << "Error al asociar el valor a la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
    }
    result = sqlite3_bind_text(stmt, 5, usuario.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        std::cerr << "Error al asociar el valor a la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
    }
    result = sqlite3_bind_text(stmt, 6, clave.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        std::cerr << "Error al asociar el valor a la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
    }

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        std::cout << "Error inserting client: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return result;
    }

    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

