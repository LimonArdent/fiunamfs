#include "ls.h"

int fiunamfs_ls(FILE* imagen){
    // Buffer para lecturas
    char buf[16];
    memset(buf, 0, 16);

    // Obtener datos del sistema de archivos
    fiunamfs_fs* str_datos = fiunamfs_stat_fs(imagen);

    fseek(imagen, str_datos->tam_cluster, SEEK_SET);
    for (size_t i=0; i<((str_datos->clusters_directorio*str_datos->tam_cluster)>>6); i++){
        char arc_tipo = fgetc(imagen);
        if (arc_tipo == 0x2d){
            // Leer nombre de archivo
            fread(buf, 1, 15, imagen);
            printf("%-20s", buf);

            // Leer tamaño de archivo en bytes
            fread(buf, 1, 4, imagen);
            printf("%-12u", fiunamfs_int32(buf));

            // Leer cluster de archivo
            fread(buf, 1, 4, imagen);
            printf("%-6u", fiunamfs_int32(buf));

            // Leer fecha de creación de archivo
            fread(buf, 1, 14, imagen);
            printf("%-16s", buf);

            // Leer fecha de última modificación de archivo
            fread(buf, 1, 14, imagen);
            printf("%-16s\n", buf);

            fseek(imagen, 12, SEEK_CUR);
        } else if (arc_tipo == 0x2f){
            // Entrada vacía
            fseek(imagen, 63, SEEK_CUR);
            continue;
        }
    }
    return 0;
}
