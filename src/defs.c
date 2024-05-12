#include "defs.h"

void fiunamfs_check_stderr(){
    switch (errno){
        case 0:
            return;
        case 2:
            fputs("El archivo no existe", stderr);
            break;
        case 13:
            fputs("No tienes permisos para abrir ese archivo", stderr);
            break;
        case 21:
            fputs("Intentas abrir una carpeta", stderr);
            break;
        default:
            fputs("Hubo un error al abrir el archivo", stderr);
    }
    exit(EXIT_FAILURE);
}

void fiunamfs_check_err(int err){
    switch (err){
        case 0:
            return;
        case ERR_NOFS:
            puts("El archivo leído no es un sistema de archivos FiUnamFS"); 
            break;
        case ERR_NOFSVER:
            puts("La versión del sistema de archivos del disco no es compatible con la versión implementada");
            break;
    }
    exit(EXIT_FAILURE);
}
