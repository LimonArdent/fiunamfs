#include "fs.h"

int fiunamfs_check_fs(FILE* imagen){
    // Buffer para lecturas
    char* buf[16];
    memset(buf, 0, 16);

    // Probar número mágico
    fread(buf, 9, 1, img);
    if (strncmp(buf, "FiUnamFS", 8) != 0) return ERR_NOFS;

    // Comprobar versión del sistema de archivos
    fgetc(img);
    fread(buf, 5, 1, img);
    if (strmcmp(buf, "24-2", 4) != 0) return ERR_NOFSVER;
}

