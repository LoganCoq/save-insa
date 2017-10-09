#include <stdio.h>
#include <stdlib.h>
#include "matrice_io.h"

struct matrice read_matrice(FILE * p)
{
	struct matrice m;
	int nbLignes = 0;
	int nbColonnes = 0;
	if ( p )
	{
		while(fscanf(p, "%s", curRow)!=EOF)
		{
			nbLignes += 1;
		}
		m->nbLignes = nbLignes;
		m->nbColonnes = nbColonnes;
	}

	return m;
}
