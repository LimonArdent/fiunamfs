#include "fs.h"

FILE* fiunamfs_open_fs(const char* ruta){
    // Buffer para lecturas
    char buf[16];
    memset(buf, 0, 16);

    FILE* img = fopen(ruta, "rb+");
    if (img == NULL) return NULL;

    // Obtener tamaño de archivo
    fseek(img, 0L, SEEK_END);
    uint32_t tam_unidad_real = ftell(img);
    printf("Tamaño real: %u\n", tam_unidad_real);
    fseek(img, 0L, SEEK_SET);

    // Probar número mágico
    fread(buf, 9, 1, img);
    if (strncmp(buf, "FiUnamFS", 8) != 0){
        errno = ERR_NOFS;
        return NULL;
    }

    // Comprobar versión del sistema de archivos
    fseek(img, 1, SEEK_CUR);
    fread(buf, 5, 1, img);
    if (strncmp(buf, "24-2", 4) != 0){
        errno = ERR_NOFSVER;
        return NULL;
    }

    // Obtener tamaño de cluster en bytes
    fseek(img, 25, SEEK_CUR);
    fread(buf, 1, 4, img);
    uint32_t tam_cluster = ((unsigned char) buf[0]) + (((unsigned char) buf[1])<<8) + (((unsigned char) buf[2])<<16) + (((unsigned char) buf[3])<<24);
    printf("Tamaño de cluster: %u\n", tam_cluster);

    // Obtener tamaño de directorio informado
    fseek(img, 1, SEEK_CUR);
    fread(buf, 1, 4, img);
    uint32_t tam_dir = ((unsigned char) buf[0]) + (((unsigned char) buf[1])<<8) + (((unsigned char) buf[2])<<16) + (((unsigned char) buf[3])<<24);
    printf("Tamaño de directorio en clusters: %u\n", tam_dir);

    // Obtener tamaño de unidad informado
    fseek(img, 1, SEEK_CUR);
    fread(buf, 1, 4, img);
    uint32_t tam_unidad = ((unsigned char) buf[0]) + (((unsigned char) buf[1])<<8) + (((unsigned char) buf[2])<<16) + (((unsigned char) buf[3])<<24);
    printf("Tamaño de unidad: %u\n", tam_unidad);

    // Comprobar tamaño de unidad
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

    return NULL;
}
