/*
 * log.c
 *
 *  Created on: Apr 3, 2023
 *      Author: unaialonso
 */

#include <stdio.h>
#include <time.h>
#include "log.h"


void logMensaje(char* mensaje) {
   time_t t = time(NULL);
   struct tm *tm = localtime(&t);
   char file[] = "logger.txt";
   FILE* fp = fopen(file, "a");
   if(fp != NULL) {
      fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d - %s\n",
         tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
         tm->tm_hour, tm->tm_min, tm->tm_sec, mensaje);
      fclose(fp);
   }
}
