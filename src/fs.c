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
    uint32_t tam_cluster = fiunamfs_int32(buf);
    printf("Tamaño de cluster: %u\n", tam_cluster);

    // Obtener tamaño de directorio informado
    fseek(img, 1, SEEK_CUR);
    fread(buf, 1, 4, img);
    uint32_t tam_dir = fiunamfs_int32(buf);
    printf("Tamaño de directorio en clusters: %u\n", tam_dir);

    // Obtener tamaño de unidad informado
    fseek(img, 1, SEEK_CUR);
    fread(buf, 1, 4, img);
    uint32_t tam_unidad = fiunamfs_int32(buf);
    printf("Tamaño de unidad: %u\n", tam_unidad);

    // Comprobar tamaño de unidad
    if (tam_unidad_real != tam_unidad*tam_cluster){
        errno = ERR_BADDRVSZ;
        return NULL;
    }

    // Crear un índice
    char* clusters = (char*) calloc(fiunamfs_bools_tam(tam_unidad), 1);
    for (size_t i=0; i<=(tam_dir); i++)
        fiunamfs_bools_set(clusters, i, true);

    // Comprobar entradas del directorio
    fseek(img, tam_cluster, SEEK_SET);
    for (size_t i=0; i<((tam_dir*tam_cluster)>>6); i++){
        char arc_tipo = fgetc(img);
        if (arc_tipo == 0x2d){
            printf("(%lu de %u) %lu: %x\n", i, ((tam_dir*tam_cluster)>>6), ftell(img), arc_tipo);
            // Archivo regular
            fseek(img, 15, SEEK_CUR);
            fread(buf, 1, 4, img);
            uint32_t arc_tam = fiunamfs_int32(buf);
            fread(buf, 1, 4, img);
            uint32_t arc_cluster = fiunamfs_int32(buf);
            for (size_t j=0; j<(arc_tam/tam_cluster+1); j++){
                bool val_cluster = fiunamfs_bools_get(clusters, arc_cluster+j);
                if (val_cluster){
                    errno = ERR_OVERCLUST;
                    free(clusters);
                    return NULL;
                } else fiunamfs_bools_set(clusters, arc_cluster+j, true);
            }
            fseek(img, 40, SEEK_CUR);
        }
        else if (arc_tipo == 0x2f){
            // Entrada vacía
            fseek(img, 63, SEEK_CUR);
            continue;
        }
        else {
            errno = ERR_BADDIRITEM;
            free(clusters);
            return NULL;
        }
    }
    free(clusters);

    return img;
}
