/*
 * File: defs.h
 * Incluye definiciones misceláneas
 */

#ifndef FIUNAMFS_DEFS
#define FIUNAMFS_DEFS

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR_NOFS 1
#define ERR_NOFSVER 2

/*
 * Muestra y trata errores POSIX estándar
 */
void fiunamfs_check_stderr();

/*
 * Muestra y trata errores FiUnamFS
 * @param err Error devuelto por una función FiUnamFS
 */
void fiunamfs_check_err(int err);

#endif
