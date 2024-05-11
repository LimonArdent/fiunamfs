#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

typedef struct {
    char etiqueta[16];
    uint32_t tam_cluster;
    uint32_t clusters_directorio;
    uint32_t clusters_unidad;
} fs_datos;

typedef struct {
    unsigned char tipo;
    char nombre[15];
    uint32_t tamano;
    uint32_t cluster;
    time_t f_creacion;
    time_t f_modificacion;
} fs_entdir;

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
    // Buffer para lecturas
    char* buf = (char*) calloc(1, 16);
    if (buf == NULL){
        puts("Error de memoria");
        free(buf);
        exit(EXIT_FAILURE);
    }

    // Necesita pasar la ruta de archivo como parámetro
    if (argc < 2){
        puts("Necesitas parámetros");
        free(buf);
        exit(EXIT_FAILURE);
    }

    // Comprobar abrir
    FILE *img = fopen(argv[1], "rb+");
    if (img == NULL){
        puts("El archivo no pudo ser abierto");
        free(buf);
        exit(EXIT_FAILURE);
    }

    // Probar número mágico
    fread(buf, 9, 1, img);
    if (strncmp(buf, "FiUnamFS", 8) != 0){
        puts("El archivo leído no es un sistema de archivos FiUnamFS");
        free(buf);
        exit(EXIT_FAILURE);
    }

    // Comprobar versión del sistema de archivos
    fgetc(img);
    fread(buf, 5, 1, img);
    printf("%s\n", buf);
    if (strncmp(buf, "24-2", 4) != 0){
        puts("La versión del sistema de archivos del disco no es compatible con la versión implementada");
        free(buf);
        exit(EXIT_FAILURE);
    }

    fclose(img);
    free(buf);
    exit(EXIT_SUCCESS);
}
