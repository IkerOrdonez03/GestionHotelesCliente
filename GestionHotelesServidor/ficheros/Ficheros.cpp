/*
 * Ficheros.cpp
 *
 *  Created on: May 24, 2023
 *      Author: unaialonso
 */

#include "ficheros.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

void guardarReserva(int id, Fecha fa_ini, Fecha fa_fin, int id_hotel, int num_Personas) {

    std::ofstream fichero;
    fichero.open("reservas.txt", std::ios::app);


    fichero << id << "|" << fa_ini.dia << "/" << fa_ini.mes << "/" << fa_ini.anyo << "|"
            << fa_fin.dia << "/" << fa_fin.mes << "/" << fa_fin.anyo << "|" << id_hotel << "|"
            << num_Personas << "\n";


    fichero.close();
}

void guardarHotel(int id, char* nom, int numEst, int idProv) {
    std::ofstream fichero("hoteles.txt", std::ios::app);

    if (!fichero) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        exit(EXIT_FAILURE);
    }

    fichero << id << " " << nom << " " << numEst << " " << idProv << std::endl;

    fichero.close();
}
