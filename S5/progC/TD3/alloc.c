#include <stdlib.h>
#include <stdio.h>
#include "alloc.h"

matrice allouer_matrice(int nb_lignes, int nb_colonnes)
{
	matrice * newMat;
	newMat = NULL;
	newMat = malloc(sizeof(matrice));
	newMat->nb_lignes = nb_lignes;
	newMat->nb_colonnes = nb_colonnes;
	 
	int tab[nb_lignes][nb_colonnes];
	tab = malloc(sizeof(int)*(nb_lignes*nb_colonnes));
	newMat->m = &tab;

	return newMat;
}

void detruire_matrice(matrice *m)
{
	free(m->m);
	free(m);
}
