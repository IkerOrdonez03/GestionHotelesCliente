/*
 * MetodosInterfaz.cpp
 *
 *  Created on: May 22, 2023
 *      Author: unaialonso
 */

//Pongo aqui los metodos de la interfaz para de momento no dar errores en el main
#include <iostream>
#include "Provincia.h"
#include "Hotel.h"
#include "Provincia.h"
#include <sqlite3.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

void menuAdmin(Provincia *provincias, Hotel* hoteles, sqlite3* db);
void loginAdmin (sqlite3* db);



void menuEliminarHotel(Provincia* provincias, Hotel* hoteles, sqlite3* db) {
    char str[10];
    int opcion;
    std::cout << "=================\nELIMINAR HOTEL\n=================\n";
    int n;
    for (n = 0; n < provincias->numProvincias; ++n) {
        std::cout << provincias[n].getId() + 1 << ". ";
        provincias[n].imprimirProvincia();
    }
    std::cout << n + 1 << ". Atras\n";
    std::cout << "Opcion: ";
    std::fflush(stdout);
    std::cin.getline(str, 10);
    sscanf(str, "%d", &opcion);
    opcion--;

    if (provincias[opcion].getId() == opcion) {
        std::cout << "=================\nMOSTRAR HOTELES\n=================";
        int j;
        char nombreProvincia[20];
        strcpy(nombreProvincia, provincias[opcion].getNombre());
        std::cout << "\nHoteles de la provincia de " << nombreProvincia << ":\n";
        for (j = 0; j < hoteles->numHoteles; ++j) {
            if (strcmp(hoteles[j].provincia->getNombre(), nombreProvincia) == 0) {
                std::cout << "ID: " << hoteles[j].getId();
                std::cout << "Nombre del Hotel: " << hoteles[j].getNombre() << std::endl;
                if(hoteles[j].getEstrellas() <=5){
                	for(int i = 0; i < hoteles[j].getEstrellas(); i++){
                		std::cout << "*";
                	}
                	std::cout << std::endl;
            }
        }
        }
        std::cout << "Opcion: ";
        std::fflush(stdout);
        std::cin.getline(str, 10);
        sscanf(str, "%d", &opcion);
        for (int i = 0; i < hoteles->numHoteles; ++i) {
            if (opcion == hoteles[i].getId()) {
                eliminarHotel(hoteles[i], db);
            }
        }
    } else if (opcion == n + 1) {
    	menuAdmin(provincias, hoteles, db);
	} else {
        std::cout << "Opcion incorrecta!\n";
        menuEliminarHotel(provincias, hoteles, db);
    }
}

Hotel menuAnadirHotel(Provincia* provincias){
    Hotel hotel;
    int idProv = 0;
    std::cout << "=================\nAÑADIR HOTEL\n=================\n";
    std::cout << "Nombre: ";
    std::fflush(stdout);
    std::cin >> hotel.getNombre();

    do {
        std::cout << "estrellas: ";
        std::fflush(stdout);
        std::cin >> hotel.estrellas;
    } while (hotel.estrellas < 1 || hotel.estrellas > 5);

    for (int i = 0; i < provincias->numProvincias; ++i) {
        std::cout << provincias[i].id << ". " << provincias[i].getNombre() << "\n";
    }

    do {
        std::cout << "Opcion: ";
        std::fflush(stdout);
        std::cin >> idProv;
    } while (idProv < 0 || idProv > provincias->numProvincias - 1);

    hotel.provincia = &(provincias[idProv]);

    return hotel;
}

void mostrarHoteles(Provincia* provincias, int eleccion, Hotel* hoteles, sqlite3* bd) {
    std::cout << "\n\n\n=================\nMOSTRAR HOTELES\n=================";

    int n;
    char nombreProvincia[20];
    strcpy(nombreProvincia, provincias[eleccion].getNombre());
    std::cout << "\nHoteles de la provincia de " << nombreProvincia << ":\n";

    for (n = 0; n < hoteles->numHoteles; ++n) {
        if (strcmp(hoteles[n].provincia->getNombre(), nombreProvincia) == 0) {
            std::cout << "Nombre del Hotel: " << hoteles[n].getNombre() << std::endl;
            if(hoteles[n].getEstrellas() <=5){
            	for(int i = 0; i < hoteles[n].getEstrellas(); i++){
            		std::cout << "*";
            	}
            	std::cout << std::endl;
            }
        }
    }

    char str[10];
    int opcion;
    std::cout << "99. Menu principal\nOpcion: ";
    std::cin.getline(str, 10);
    sscanf(str, "%d", &opcion);

    if (opcion == 99) {
        std::cout << "\n\n\n";
        menuAdmin(provincias, hoteles, bd);
    }
}

void menuProvinciasHoteles(Provincia* provincias, Hotel* hoteles, sqlite3* db) {
    char str[10];
    int opcion;
    std::cout << "\n\n\n=================\nMOSTRAR HOTELES\n=================";
    std::cout << "\nProvincias:\n";
    int n;
    for (n = 0; n < provincias->numProvincias; ++n) {
        std::cout << n + 1 << ". ";
        provincias[n].imprimirProvincia();
    }
    std::cout << n + 1 << ". Atras\n";
    std::cout << "Opcion: ";
    std::fflush(stdout);
    std::cin.getline(str, 10);
    sscanf(str, "%d", &opcion);

    if (opcion > 0 && opcion <= n) {
        std::cout << "Opcion provincias check\n";
        mostrarHoteles(provincias, opcion - 1, hoteles, db);
    } else if (opcion == n + 1) {
        std::cout << "\n\n\n";
        menuAdmin(provincias, hoteles, db);
    } else {
        std::cout << "Opcion incorrecta!!!\n";
        menuProvinciasHoteles(provincias, hoteles, db);
    }
}



void menuAdmin(Provincia* provincias, Hotel* hoteles, sqlite3* db) {
    char str[10];
    int opcion;
    std::cout << "============\nMENU ADMIN\n============\n";
    std::cout << "\n1. Mostrar hoteles existentes.\n2. Añadir hotel.";
    std::cout << "\n3. Eliminar hotel.\n4. Mostrar reservas realizadas por distintos usuarios.";
    std::cout << "\n5. Salir.\nOpcion: ";

    while (opcion < 6 || opcion > 0) {
        std::fflush(stdout);
        std::cin.getline(str, 10);
        sscanf(str, "%d", &opcion);

        if (opcion == 1) { // MOSTRAR HOTELES
            menuProvinciasHoteles(provincias, hoteles, db);
        } else if (opcion == 2) { // AÑADIR HOTEL
            Hotel hotel;
            hotel = menuAnadirHotel(provincias);

            std::cout << "Nombre del Hotel: " << hotel.getNombre() << std::endl;
            if(hotel.getEstrellas() <=5){
            	for(int i = 0; i < hotel.getEstrellas(); i++){
            		std::cout << "*";
            	}
            std::cout << std::endl;

            insertarHotel(&hotel, db);
        } else if (opcion == 3) { // ELIMINAR HOTEL
            menuEliminarHotel(provincias, hoteles, db);
        } else if (opcion == 4) { // MOSTRAR RESERVAS
            std::cout << "Proximamente disponible...\n";
            opcion = 5;
        } else if (opcion == 5) { // SALIR
            std::exit(EXIT_FAILURE);
        }
    }
}
}

void menuAdmin(Provincia* provincias, Hotel* hoteles, sqlite3* db) {
    char str[10];
    int opcion;
    std::cout << "============\nMENU ADMIN\n============\n";
    std::cout << "\n1. Mostrar hoteles existentes.\n2. Anadir hotel.";
    std::cout << "\n3. Eliminar hotel.\n4. Mostrar reservas realizadas por distintos usuarios.";
    std::cout << "\n5. Salir.\nOpcion: ";

    while (opcion < 6 || opcion > 0) {
        std::fflush(stdout);
        std::cin.getline(str, 3);
        sscanf(str, "%d", &opcion);
        if (opcion == 1) { // MOSTRAR HOTELES
            menuProvinciasHoteles(provincias, hoteles, db);
        } else if (opcion == 2) { // ANADIR HOTEL
            Hotel hotel;
            hotel = menuAnadirHotel(provincias);
            imprimirHotel(&hotel);
            insertarHotel(&hotel, db);
        } else if (opcion == 3) { // ELIMINAR HOTEL
            menuEliminarHotel(provincias, hoteles, db);
        } else if (opcion == 4) { // MOSTRAR RESERVAS
            std::cout << "Proximamente disponible...\n";
            opcion = 5;
        } else if (opcion == 5) { // SALIR
            exit(EXIT_FAILURE);
        }
    }
}













