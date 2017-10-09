#ifndef __MATRICE_IO_H__
#define __MATRICE_IO_H__

struct matrice read_matrice(FILE * p);

void write_matrice(FILE * p, struct matrice m);

#endif
