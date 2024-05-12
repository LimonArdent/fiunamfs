/*
 * File: fs.h
 * Incluye funciones para administrar un sistema de archivos existente
 */

#ifndef FIUNAMFS_FS
#define FIUNAMFS_FS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "defs.h"

typedef struct {
    char etiqueta[16];
    uint32_t tam_cluster;
    uint32_t clusters_directorio;
    uint32_t clusters_unidad;
} fiunamfs_fs;

/*
 * Valida si el sistema de archivos está en buen estado
 * @param imagen Puntero al sistema de archivos
 * @return 0 si la tarea tuvo éxito, 1 si no
 */
int fiunamfs_check_fs(FILE* imagen);

/*
 * Devuelve una estructura con información sobre el sistema de archivos
 * @param imagen Puntero al sistema de archivos
 * @return 0 si la tarea tuvo éxito, 1 si no
 */
int fiunamfs_stat_fs(FILE* imagen);

#endif
