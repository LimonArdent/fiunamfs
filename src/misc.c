#include "misc.h"

size_t fiunamfs_bools_tam(size_t n){
    return ((n-1)/8)+1;
}

void fiunamfs_bools_set(char* a, size_t p, bool v){
    if (v) a[p/8] |= (1<<(p%8));
    else a[p/8] &= ~(1<<(p%8));
    return;
}

bool fiunamfs_bools_get(char* a, size_t p){
    return a[p/8] & (1<<(p%8));
}

uint32_t fiunamfs_int32(char* a){
   return ((unsigned char) a[0]) + (((unsigned char) a[1])<<8) + (((unsigned char) a[2])<<16) + (((unsigned char) a[3])<<24);
}
