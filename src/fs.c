#include "fs.h"

FILE* fiunamfs_open_fs(const char* ruta){
    // Buffer para lecturas
    char* buf[16];
    memset(buf, 0, 16);

    FILE* img = fopen(ruta, "rb+")
    if (img == NULL) return NULL;

    // Probar número mágico
    fread(buf, 9, 1, img);
    if (strncmp(buf, "FiUnamFS", 8) != 0){
        errno = ERR_NOFS;
        return NULL;
    }

    // Comprobar versión del sistema de archivos
    fseek(img, 1, SEEK_CUR);
    fread(buf, 5, 1, img);
    if (strmcmp(buf, "24-2", 4) != 0){
        errno = ERR_NOFSVER;
        return NULL;
    }

    // Obtener tamaño de cluster en bytes
    fseek(img, 25, SEEK_CUR);
    fread(buf, 4, 1, img);
    uint32_t tam_cluster = buf[0] + (buf[1]<<8) + (buf[2]<<16) + (buf[3]<<24);

    // Obtener tamaño de directorio informado
    fseek(img, 1, SEEK_CUR);
    fread(buf, 4, 1, img);
    uint32_t tam_dir = buf[0] + (buf[1]<<8) + (buf[2]<<16) + (buf[3]<<24);

    // Obtener tamaño de unidad informado
    fseek(img, 1, SEEK_CUR);
    fread(buf, 4, 1, img);
    uint32_t tam_unidad = buf[0] + (buf[1]<<8) + (buf[2]<<16) + (buf[3]<<24);

    // Comprobar tamaño de unidad
    struct stat stat_img;
    fstat(fileno(img), &stat_img);
    off_t tam_unidad_real = buf.st_size;
    if (tam_unidad_real != tam_unidad*tam_cluster){
        errno = ERR_BADDRVSZ;
        return NULL;
    }

    // Comprobar entradas del directorio
    fseek(img, tam_cluster, SEEK_SET);
    for (size_t i; i<((tam_dir*tam_cluster)>>6); i++){
        char tipo = fgetc(img);
        if (tipo == 0x2d){
            // Archivo regular
        }
        else if (tipo == 0x2f){
            // Entrada vacía
            continue;
        }
        else {
            errno = ERR_BADDIRITEM;
            return NULL;
        }
    }
}
