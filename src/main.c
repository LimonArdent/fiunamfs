#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "defs.h"

/*
Enteros: 4b, le
0-8: FiUnamFS
10-14: Versión: 24-2
20-35: Etiqueta
40-44: Tamaño de cluster
45-49: Número de clusters que mide el directorio
50-54: Número de clusters que mide la unidad completa

Directorio:
0: Tipo: archivo0x2d, vacio: 0x2f
1-15: Nombre de archivo
16-20: tamaño en bytes
20-23: cluster inicial
24-37: Hora y fecha de creación AAAAMMDDHHMMSS
38-51: ídem, modificación
52-64: reservado

Entradas no utilizadas: ###############
Cada cluster mide 4 sectores, cada sector mide 512 bytes
ver htons ntohs
*/


int main (int argc, char* argv[]){
    // Necesita pasar la ruta de archivo como parámetro
    if (argc < 2){
        puts("Necesitas parámetros");
        exit(EXIT_FAILURE);
    }

    // Comprobar abrir
    FILE *img = fopen(argv[1], "rb+");
    if (img == NULL) fiunamfs_check_stderr();

    fclose(img);
    exit(EXIT_SUCCESS);
}
