#include "error.h"

void fiunamfs_check_err(){
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
        case ERR_NOFS:
            puts("El archivo leído no es un sistema de archivos FiUnamFS");
            break;
        case ERR_NOFSVER:
            puts("La versión del sistema de archivos del disco no es compatible con la versión implementada");
            break;
        case ERR_BADDRVSZ:
            puts("El tamaño de unidad informado en el sistema de archivos no corresponde con la realidad");
            break;
        case ERR_BADDIRITEM:
            puts("Una entrada del directorio tiene un tipo de inodo no reconocido");
            break;
        case ERR_OVERCLUST:
            puts("Un cluster pertenece a más de una entrada de directorio");
            break;
        case ERR_MEMORY:
            puts("Hubo un error al momento de pedir memoria");
            break;
        default:
            fputs("Hubo un error al abrir el archivo", stderr);
    }
    exit(EXIT_FAILURE);
}
