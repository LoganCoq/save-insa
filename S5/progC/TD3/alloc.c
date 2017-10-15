#include <stdlib.h>
#include <stdio.h>
#include "alloc.h"
#include "matrice.h"

matrice allouer_matrice(int nb_lignes, int nb_colonnes)
{
	matrice newMat;
	newMat.nb_lignes = nb_lignes;
	newMat.nb_colonnes = nb_colonnes;

	newMat.m = calloc(nb_lignes, sizeof(int *));
	int i = 0;
  	for(i=0; i<nb_lignes; i++)
		newMat.m[i] = calloc(nb_colonnes, sizeof(int));

	return newMat;
}

void detruire_matrice(matrice *m)
{
	int i = 0;
	for(i=0; i<m->nb_lignes; i++)
		free(m->m[i]);
	free(m->m);
	m->m = NULL;
}
