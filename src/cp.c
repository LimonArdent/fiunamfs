#include "cp.h"

int fiunamfs_cp_fuera(FILE* imagen, const char* ruta_dentro, const char* ruta_fuera){
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
            memset(buf, 0, 16);
            fread(buf, 1, 15, imagen);

            // Normalizar espacios al final y comparar
            for (int j=15; j>=0 && (buf[j] == ' ' || buf[j] == 0); j--) buf[j] = 0;
            if (!strcmp(buf, ruta_dentro)){
                // Leer tamaño de archivo en bytes
                fread(buf, 1, 4, imagen);
                uint32_t arc_tam = fiunamfs_int32(buf);

                // Leer cluster de archivo
                fread(buf, 1, 4, imagen);
                uint32_t arc_cluster = fiunamfs_int32(buf);

                // Copiar archivo hacia afuera
                FILE* destino = fopen(ruta_fuera, "wb+");
                if (destino == NULL) return 1;

                fseek(imagen, arc_cluster*str_datos->tam_cluster, SEEK_SET);
                for (size_t k=0; k<arc_tam; k++) fputc(fgetc(imagen), destino);

                fclose(destino);
                return 0;
            }

            fseek(imagen, 47, SEEK_CUR);
        } else if (arc_tipo == 0x2f){
            // Entrada vacía
            fseek(imagen, 63, SEEK_CUR);
            continue;
        }
    }
    errno = ENOENT;
    return 1;
}
