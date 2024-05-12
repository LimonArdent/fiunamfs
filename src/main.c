#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "fs.h"

/*
Directorio:
0: Tipo: archivo0x2d, vacio: 0x2f
1-15: Nombre de archivo
16-20: tamaño en bytes
20-23: cluster inicial
24-37: Hora y fecha de creación AAAAMMDDHHMMSS
38-51: ídem, modificación
52-64: reservado

Entradas no utilizadas: ###############
*/


int main (int argc, char* argv[]){
    // Necesita pasar la ruta de archivo como parámetro
    if (argc < 2){
        puts("Necesitas parámetros");
        exit(EXIT_FAILURE);
    }

    // Comprobar abrir
    FILE *img = fiunamfs_open_fs(argv[1]);
    if (img == NULL) fiunamfs_check_err();

    fclose(img);
    exit(EXIT_SUCCESS);
}
