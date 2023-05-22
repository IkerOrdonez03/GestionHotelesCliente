/*
 * fecha.h
 *
 *  Created on: Apr 5, 2023
 *      Author: unaialonso
 */

#ifndef FECHA_FECHA_H_
#define FECHA_FECHA_H_

typedef struct{
	int anyo;
	int mes;
	int dia;
}Fecha;

void imprimirFecha(Fecha f);

#endif /* FECHA_FECHA_H_ */
