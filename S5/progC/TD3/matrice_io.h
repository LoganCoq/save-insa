#ifndef __MATRICE_IO_H__
#define __MATRICE_IO_H__

#include "matrice.h"

matrice read_matrice(FILE * p);

void write_matrice(FILE * p, matrice m);

void affiche_matrice(matrice m);

#endif
