/*
 * reserva.c
 *
 *  Created on: Apr 5, 2023
 *      Author: unaialonso
 */

#include "reserva.h"


void imprimirReserva(Reserva r){

	printf("Reserva %d, ", r.idRes);
	imprimirFecha(r.fechaIni);
	imprimirFecha(r.fechaFin);
	printf(", Hab: %d, DNI: %d\n", r.idHab, r.dni);
}
