#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "fs.h"
#include "ls.h"

int main (int argc, char* argv[]){
    // Necesita pasar la ruta de archivo como parámetro
    if (argc < 2){
        fputs("Necesitas especificar un comando", stderr);
        exit(EXIT_FAILURE);
    } else if (argc < 3){
        fputs("Necesitas especificar la ruta de la imagen", stderr);
        exit(EXIT_FAILURE);
    } else if (!strcmp(argv[1], "ayuda")){
        printf("Uso: %s <comando> <imagen> [parámetros]\n", argv[0]);
        puts("Comandos disponibles:");
        puts("  ayuda - muestra esta ayuda");
        puts("  ls - lista los archivos del sistema de archivos");
        puts("  cpo - copia un archivo del sistema de archivos hacia tu equipo");
        puts("  cpi - copia un archivo de tu equipo hacia el sistema de archivos");
        puts("  rm - elimina un archivo del sistema de archivos");
        exit(EXIT_SUCCESS);
    }

    // Comprobar imagen de disco
    FILE *imagen = fiunamfs_open_fs(argv[1]);
    if (imagen == NULL) fiunamfs_check_err();

    if (!strcmp(argv[1], "ls")){
        fiunamfs_ls(imagen);
    } else if (!strcmp(argv[1], "cpo")){
    } else if (!strcmp(argv[1], "cpi")){
    } else if (!strcmp(argv[1], "rm")){
    } else {
        fprintf(stderr, "No existe el comando %s\n", argv[1]);
    }

    fclose(imagen);
    exit(EXIT_SUCCESS);
}
