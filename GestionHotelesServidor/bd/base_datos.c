#include "base_datos.h"
#include <stdlib.h>

char mensaje[100];

int validadAdmin(char* usuario, char* clave, sqlite3 *db) {
	char c[30];

	sqlite3_stmt *stmt;
	char sql[] = "SELECT CLAVE_ADMIN FROM ADMINISTRADOR WHERE USUARIO_ADMIN = ?";
	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		strcpy(mensaje, strcat("Error preparing statement (SELECT)", sqlite3_errmsg(db)));
		logMensaje(mensaje);
	}
	else {
		strcpy(mensaje,"SQL query prepared (SELECT)");
		logMensaje(mensaje);
	}
	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
	result = sqlite3_step(stmt) ;
	if (result == SQLITE_ROW) {
		strcpy(c, (char *) sqlite3_column_text(stmt, 0));
	}
	result = sqlite3_finalize(stmt);
	return strcmp(c, clave);
}

int contarProvincias(sqlite3 *db) {
	int contador;
	sqlite3_stmt *stmt;
		char sql[] = "SELECT COUNT(ID_PROV) FROM PROVINCIA";

		int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
		if (result != SQLITE_OK) {
			strcpy(mensaje, strcat("Error preparing statement (SELECT)", sqlite3_errmsg(db)));
			logMensaje(mensaje);
		}
		else {
			strcpy(mensaje,"SQL query prepared (SELECT)");
			logMensaje(mensaje);
		}

		result = sqlite3_step(stmt) ;
			if (result == SQLITE_ROW) {
				contador = sqlite3_column_int(stmt, 0);
			}
		result = sqlite3_finalize(stmt);


		return contador;
}

int initProvincias (Provincias* provincias, sqlite3 *db) {
	sqlite3_stmt *stmt;
	char sql[] = "SELECT ID_PROV, NOM_PROV FROM PROVINCIA";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		strcpy(mensaje, strcat("Error preparing statement (SELECT)", sqlite3_errmsg(db)));
		logMensaje(mensaje);
	}
	else {
		strcpy(mensaje,"SQL query prepared (SELECT)");
		logMensaje(mensaje);
	}
	for (int i = 0; i < (*provincias).numProvincias; ++i) {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			(*provincias).provincias[i].id = sqlite3_column_int(stmt, 0);
			strcpy((*provincias).provincias[i].name, (char *) sqlite3_column_text(stmt, 1));
		}
	}
	result = sqlite3_finalize(stmt);
	return result;

}

int contarHoteles(sqlite3 *db) {
	int contador;
	sqlite3_stmt *stmt;
		char sql[] = "SELECT COUNT(ID_HOTEL) FROM HOTEL";

		int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
		if (result != SQLITE_OK) {
			strcpy(mensaje, strcat("Error preparing statement (SELECT)", sqlite3_errmsg(db)));
			logMensaje(mensaje);
		}
		else {
			strcpy(mensaje,"SQL query prepared (SELECT)");
			logMensaje(mensaje);
		}
		result = sqlite3_step(stmt) ;
			if (result == SQLITE_ROW) {
				contador = sqlite3_column_int(stmt, 0);
			}
		result = sqlite3_finalize(stmt);

		return contador;
}

int initHoteles (Hoteles * hoteles, sqlite3 *db, Provincias * provincias) {
	sqlite3_stmt *stmt;
	char sql[] = "SELECT ID_HOTEL, NOM_HOTEL, NUM_ESTTRELLAS, ID_PROV FROM HOTEL";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		strcpy(mensaje, strcat("Error preparing statement (SELECT)", sqlite3_errmsg(db)));
		logMensaje(mensaje);
	}
	else {
		strcpy(mensaje,"SQL query prepared (SELECT)");
		logMensaje(mensaje);
	}
	for (int i = 0; i < (*hoteles).numHoteles; ++i) {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			(*hoteles).hoteles[i].id = sqlite3_column_int(stmt, 0);
			strcpy((*hoteles).hoteles[i].name, (char *) sqlite3_column_text(stmt, 1));
			(*hoteles).hoteles[i].estrellas = sqlite3_column_int(stmt, 2);
			for (int n = 0; n < contarProvincias(db); ++n) {
				if (provincias->provincias[n].id == sqlite3_column_int(stmt, 3)) {
					(*hoteles).hoteles[i].provincia = &(*provincias).provincias[n];
				}
			}

		}
	}

	result = sqlite3_finalize(stmt);

	return result;

}

int insertarHotel (Hotel * hotel, sqlite3 *db) {
	sqlite3_stmt *stmt;
	char sql[] = "INSERT INTO HOTEL (NOM_HOTEL, NUM_ESTTRELLAS, ID_PROV) VALUES (?, ?, ?)";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;

	if (result != SQLITE_OK) {
		strcpy(mensaje, strcat("Error preparing statement (SELECT)", sqlite3_errmsg(db)));
		logMensaje(mensaje);
	}
	else {
		strcpy(mensaje,"SQL query prepared (SELECT)");
		logMensaje(mensaje);
	}
	char nombre[50];
	strcpy(nombre, hotel->name);
	result = sqlite3_bind_text(stmt, 1, nombre, strlen(nombre) + 1, SQLITE_STATIC);
	result = sqlite3_bind_int(stmt, 2, hotel->estrellas);
	result = sqlite3_bind_int(stmt, 3, hotel->provincia->id);
	result = sqlite3_step(stmt);
	result = sqlite3_finalize(stmt);
	return result;
}

int eliminarHotel (Hotel * hotel, sqlite3 *db) {
	sqlite3_stmt *stmt;
	char sql[] = "DELETE FROM HOTEL WHERE ID_HOTEL == ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;

	if (result != SQLITE_OK) {
		strcpy(mensaje, strcat("Error preparing statement (SELECT)", sqlite3_errmsg(db)));
		logMensaje(mensaje);
	}
	else {
		strcpy(mensaje,"SQL query prepared (SELECT)");
		logMensaje(mensaje);
	}

	result = sqlite3_bind_int(stmt, 1, hotel->id);
	result = sqlite3_step(stmt);
	result = sqlite3_finalize(stmt);

	return result;
}


// Segunda entrega
int validadCliente(char* usuario, char* clave, sqlite3 *db) {
	char c[30];

	sqlite3_stmt *stmt;
	char sql[] = "SELECT CLAVE_CLTE FROM CLIENTE WHERE USUARIO_CLTE = ?";
	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		strcpy(mensaje, strcat("Error preparing statement (SELECT)", sqlite3_errmsg(db)));
		logMensaje(mensaje);
	}
	else {
		strcpy(mensaje,"SQL query prepared (SELECT)");
		logMensaje(mensaje);
	}
	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
	result = sqlite3_step(stmt) ;
	if (result == SQLITE_ROW) {
		strcpy(c, (char *) sqlite3_column_text(stmt, 0));
	}
	result = sqlite3_finalize(stmt);
	return strcmp(c, clave);
}






