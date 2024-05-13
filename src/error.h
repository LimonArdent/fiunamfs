/*
 * File: error.h
 * Incluye funciones y macros para tratar con errores
 */

#ifndef FIUNAMFS_DEFS
#define FIUNAMFS_DEFS

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR_NOFS 201
#define ERR_NOFSVER 202
#define ERR_BADDRVSZ 203
#define ERR_BADDIRITEM 204
#define ERR_OVERCLUST 205

/*
 * Muestra y trata errores FiUnamFS
 * @param err Error devuelto por una función FiUnamFS
 */
void fiunamfs_check_err();

#endif
