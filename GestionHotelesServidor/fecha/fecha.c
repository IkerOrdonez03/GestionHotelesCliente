/*
 * fecha.c
 *
 *  Created on: Apr 5, 2023
 *      Author: unaialonso
 */
#include "fecha.h"
#include <stdio.h>


void imprimirFecha(Fecha f){
	printf("%d/%d/%d\n", f.dia, f.mes, f.anyo);
}
