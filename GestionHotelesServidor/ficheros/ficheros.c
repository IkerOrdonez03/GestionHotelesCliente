#include "ficheros.h"
#include <stdlib.h>
#include <stdio.h>


void guardarReserva(char cod_Reserva[], Fecha fa_ini, Fecha fa_fin, int id_hotel, int num_Personas) {
       // Abrir el fichero de reservas en modo "append" para agregar la nueva reserva al final del fichero
       FILE *fichero;
       fichero = fopen("reservas.txt", "a");

       // Escribir los datos de la reserva en el formato indicado, separados por barras verticales (|)
       fprintf(fichero, "%s|%s|%s|%s|%d\n", cod_Reserva, fa_ini, fa_fin, id_hotel, num_Personas);

       // Cerrar el fichero de reservas
       fclose(fichero);
   }

void guardarHotel(int id, char nom[50], int numEst, int idProv) {
    FILE *fichero;

    fichero = fopen("hoteles.txt", "a");
    if (fichero == NULL) {
        printf("Error al abrir el fichero.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fichero, "%d %s %d %d\n", id, nom, numEst, idProv);

    fclose(fichero);
}


