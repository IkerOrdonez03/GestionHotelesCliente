#ifndef FICHEROS_FICHEROS_H_
#define FICHEROS_FICHEROS_H_

#include "../hotel/hotel.h"
#include <stdio.h>
#include "../fecha/fecha.h"

void guardarReserva(char cod_Reserva[], Fecha fa_ini, Fecha fa_fin, int id_hotel, int num_Personas);

void guardarHotel(int id, char nom[20], int numEst, int idProv);

#endif /* FICHEROS_FICHEROS_H_ */
