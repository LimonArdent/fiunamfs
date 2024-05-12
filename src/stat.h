/*
 * File: stat.h
 * Incluye la función para consultar y manipular las propiedades de un archivo
 */

#ifndef FIUNAMFS_STAT
#define FIUNAMFS_STAT

#include <stdio.h>
#include <time.h>

#include "error.h"

typedef struct {
    unsigned char tipo;
    char nombre[15];
    uint32_t tamano;
    uint32_t cluster;
    time_t f_creacion;
    time_t f_modificacion;
} fiunamfs_entdir;

/*
 * Devuelve datos sobre un archivo en el sistema de archivos
 * @param imagen Puntero al sistema de archivos
 * @param ruta Nombre del archivo a analizar
 * @return 0 si la tarea tuvo éxito, 1 si no
 */
int fiunamfs_stat(FILE* imagen, const char* ruta);

#endif
