#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "fs.h"
#include "ls.h"
#include "rm.h"

int main (int argc, char* argv[]){
    // Necesita pasar la ruta de archivo como parámetro
    if (argc < 2){
        fputs("Necesitas especificar un comando\n", stderr);
        exit(EXIT_FAILURE);
    } else if (!strcmp(argv[1], "ayuda")){
        printf("Uso: %s <comando> <imagen> [parámetros]\n", argv[0]);
        puts("Comandos disponibles:");
        puts("  ayuda - muestra esta ayuda");
        puts("  ls [archivo] - lista los archivos del sistema de archivos");
        puts("  cpo [archivo] - copia un archivo del sistema de archivos hacia tu equipo");
        puts("  cpi [archivo] - copia un archivo de tu equipo hacia el sistema de archivos");
        puts("  rm [archivo] - elimina un archivo del sistema de archivos");
        exit(EXIT_SUCCESS);
    } else if (argc < 3){
        fputs("Necesitas especificar la ruta de la imagen\n", stderr);
        exit(EXIT_FAILURE);
    }

    // Comprobar imagen de disco
    FILE *imagen = fiunamfs_open_fs(argv[2]);
    if (imagen == NULL) fiunamfs_check_err();

    if (!strcmp(argv[1], "ls")){
        fiunamfs_ls(imagen);
    } else if (!strcmp(argv[1], "cpo")){
        if (argc < 4){
            fputs("Necesitas especificar el nombre del archivo a copiar", stderr);
            fclose(imagen);
            exit(EXIT_FAILURE);
        }
    } else if (!strcmp(argv[1], "cpi")){
        if (argc < 4){
            fputs("Necesitas especificar la ruta del archivo a copiar", stderr);
            fclose(imagen);
            exit(EXIT_FAILURE);
        }
    } else if (!strcmp(argv[1], "rm")){
        if (argc < 4){
            fputs("Necesitas especificar el nombre del archivo a borrar\n", stderr);
            fclose(imagen);
            exit(EXIT_FAILURE);
        }
        if (fiunamfs_rm(imagen, argv[3])) fiunamfs_check_err();
    } else {
        fprintf(stderr, "No existe el comando %s\n", argv[1]);
    }

    fclose(imagen);
    exit(EXIT_SUCCESS);
}
